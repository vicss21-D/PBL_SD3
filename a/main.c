/*
 * 
 * Image Processing System with FPGA Hardware Acceleration
 * Supports BMP loading, zoom in/out algorithms, and FPGA memory management
 * 
 */

#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

/* ===================================================================
 * CONSTANTS AND CONFIGURATION
 * =================================================================== */
#define TIMEOUT_LOOPS 50
#define REFRESH_DELAY_US 100000
#define PULSE_DELAY_US 10000

/* Zoom Level Constraints */
#define MAX_ZOOM_IN_LEVEL 3
#define MIN_ZOOM_OUT_LEVEL -3

/* ===================================================================
 * BMP FILE STRUCTURES
 * =================================================================== */
#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHeader;

typedef struct {
    uint32_t size;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bits;
    uint32_t compression;
    uint32_t imagesize;
    int32_t  xresolution;
    int32_t  yresolution;
    uint32_t ncolours;
    uint32_t importantcolours;
} BMPInfoHeader;
#pragma pack(pop)

/* ===================================================================
 * UTILITY FUNCTIONS
 * =================================================================== */

/**
 * @brief Converts RGB color to grayscale using standard luminosity formula
 */

uint8_t rgb_to_gray(uint8_t r, uint8_t g, uint8_t b) {
    return (uint8_t)((299 * r + 587 * g + 114 * b) / 1000);
}

/**
 * @brief Clears input buffer to prevent scanf issues
 */

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Waits for user to press Enter
 */

void wait_for_enter(void) {
    printf("\nPressione Enter para continuar...");
    clear_input_buffer();
    getchar();
}

/* ===================================================================
 * BMP IMAGE LOADING
 * =================================================================== */

/**
 * @brief Loads a BMP image file into memory buffer
 * @param filename Path to BMP file
 * @param image_data Output buffer for grayscale pixel data
 * @return 0 on success, -1 on failure
 */

int load_bmp(const char *filename, uint8_t *image_data) {
    FILE *file;
    BMPHeader header;
    BMPInfoHeader info_header;
   
    file = fopen(filename, "rb");
    if (!file) {
        printf(" Erro ao abrir '%s'\n", filename);
        return -1;
    }
   
    /* Read and validate BMP header */
    fread(&header, sizeof(BMPHeader), 1, file);
    if (header.type != 0x4D42) {
        printf(" Arquivo nao e BMP valido (assinatura 0x%X)\n", header.type);
        fclose(file);
        return -1;
    }
   
    /* Read and validate info header */
    fread(&info_header, sizeof(BMPInfoHeader), 1, file);
    if (info_header.width != IMG_WIDTH || abs(info_header.height) != IMG_HEIGHT) {
        printf(" Dimensao incorreta: %dx%d (esperado %dx%d)\n",
               info_header.width, abs(info_header.height), IMG_WIDTH, IMG_HEIGHT);
        fclose(file);
        return -1;
    }
   
    /* Position file pointer at pixel data */
    fseek(file, header.offset, SEEK_SET);
   
    /* Calculate row size with padding */
    int row_size = ((info_header.width * info_header.bits + 31) / 32) * 4;
   
    uint8_t *row_data = (uint8_t*)malloc(row_size);
    if (!row_data) {
        printf("\nErro ao alocar memoria para a linha do BMP\n");
        fclose(file);
        return -1;
    }
   
    /* Read and convert pixel data */
    printf("Carregando");
    for (int y = 0; y < IMG_HEIGHT; y++) {
        fread(row_data, 1, row_size, file);
       
        for (int x = 0; x < IMG_WIDTH; x++) {
            uint8_t gray;
           
            /* Handle different bit depths */
            if (info_header.bits == 32) {
                uint8_t b = row_data[x * 4 + 0];
                uint8_t g = row_data[x * 4 + 1];
                uint8_t r = row_data[x * 4 + 2];
                gray = rgb_to_gray(r, g, b);
            } else if (info_header.bits == 24) {
                uint8_t b = row_data[x * 3 + 0];
                uint8_t g = row_data[x * 3 + 1];
                uint8_t r = row_data[x * 3 + 2];
                gray = rgb_to_gray(r, g, b);
            } else if (info_header.bits == 8) {
                gray = row_data[x];
            } else {
                printf("\nFormato %d bits nao suportado\n", info_header.bits);
                free(row_data);
                fclose(file);
                return -1;
            }
           
            /* BMP rows are stored bottom-to-top */
            int addr = (IMG_HEIGHT - 1 - y) * IMG_WIDTH + x;
            image_data[addr] = gray;
        }
       
        /* Progress indicator */
        if (y % 60 == 0) {
            printf(".");
            fflush(stdout);
        }
    }
   
    printf(" OK!\n");
    free(row_data);
    fclose(file);
    return 0;
}

/* ===================================================================
 * TEST PATTERN GENERATION
 * =================================================================== */

/**
 * @brief Generates a horizontal gradient test pattern
 */

void generate_test_pattern(uint8_t *image_data) {
    printf("   [C] Gerando padrao de teste (gradiente 320x240)...\n");
    for (int y = 0; y < IMG_HEIGHT; y++) {
        for (int x = 0; x < IMG_WIDTH; x++) {
            uint8_t pixel_value = (uint8_t)((x * 255) / (IMG_WIDTH - 1));
            image_data[y * IMG_WIDTH + x] = pixel_value;
        }
    }
}

/* ===================================================================
 * FPGA COMMUNICATION
 * =================================================================== */

/**
 * @brief Sends entire image buffer to FPGA VRAM
 * @param image_data Source pixel buffer
 * @return 0 on success, -1 on failure
 */

int send_image_to_fpga(uint8_t *image_data) {
    int total_pixels = IMG_WIDTH * IMG_HEIGHT;
    int errors = 0;

    printf("   [C] Enviando %d pixels para o FPGA (testando ASM_Store)...\n", total_pixels);
   
    for (int i = 0; i < total_pixels; i++) {
        int status = ASM_Store(i, image_data[i], 0);
        if (status != 0) {
            printf("\n   [C] ERRO: ASM_Store falhou no pixel %d (codigo %d)\n", i, status);
            errors++;
            if (errors > 10) {
                printf("   [C] Muitos erros, abortando envio.\n");
                return -1;
            }
        }
    }
   
    printf("   [C] Envio de pixels OK.\n");
    printf("   [C] Testando ASM_Refresh()...\n");
    ASM_Refresh();
    usleep(REFRESH_DELAY_US);

    if (errors > 0) {
        printf("   [C] ERRO: %d falhas de escrita de pixel.\n", errors);
        return -1;
    }
    return 0;
}

/**
 * @brief Executes an algorithm on FPGA and waits for completion
 * @param algo_name Algorithm name for logging
 * @param algo_func Pointer to algorithm function
 * @return 0 on success, -1 on failure
 */
int execute_algorithm(const char *algo_name, void (*algo_func)(void)) {
    printf("   [C] Executando '%s' (assincrono)...\n", algo_name);
   
    /* Set algorithm opcode */
    algo_func();
   
    printf("   [C] Hardware iniciado. Aguardando FLAG_DONE (polling)...\n");

    /* Poll for completion */
    int timeout_counter = 0;
    while (ASM_Get_Flag_Done() == 0) {
        usleep(REFRESH_DELAY_US);
        timeout_counter++;
       
        if (timeout_counter > TIMEOUT_LOOPS) {
            printf("\n   [C] ERRO FATAL: TIMEOUT DO ALGORITMO '%s'!\n", algo_name);
            return -1;
        }
    }
   
    printf("   [C] FLAG_DONE recebida para '%s'!\n", algo_name);

    /* Check for hardware errors */
    if (ASM_Get_Flag_Error() != 0) {
        printf("   [C] ATENCAO: O FPGA reportou um ERRO (Flag_Error) durante '%s'!\n", algo_name);
        return -1;
    }

    /* Pulse enable to acknowledge completion */
    ASM_Pulse_Enable();
   
    printf("   [C] '%s' executado com sucesso.\n", algo_name);
    return 0;
}

/**
 * @brief Reads a rectangular window from FPGA memory
 * @param buffer Output buffer for pixel data
 * @param x Starting X coordinate
 * @param y Starting Y coordinate
 * @param width Window width
 * @param height Window height
 * @return 0 on success, -1 on failure
 */
int read_fpga_window(uint8_t *buffer, int x, int y, int width, int height) {
    if (!buffer) {
        printf("ERRO: Buffer nulo em read_fpga_window\n");
        return -1;
    }
   
    if (x < 0 || y < 0 || width <= 0 || height <= 0) {
        printf("ERRO: Parametros invalidos em read_fpga_window\n");
        return -1;
    }
   
    if (x + width > IMG_WIDTH || y + height > IMG_HEIGHT) {
        printf("ERRO: Janela fora dos limites da imagem\n");
        return -1;
    }
   
    int buffer_index = 0;
    int errors = 0;
   
    printf("   [C] Lendo janela (%d,%d) com tamanho %dx%d da FPGA...\n",
           x, y, width, height);
   
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int addr = (y + row) * IMG_WIDTH + (x + col);
            int pixel_value = ASM_Load(addr, 1);
           
            if (pixel_value < 0 || pixel_value > 255) {
                printf("   [C] AVISO: Valor invalido no pixel [%d,%d]: %d\n",
                       x + col, y + row, pixel_value);
                errors++;
                pixel_value = 0;
            }
           
            buffer[buffer_index++] = (uint8_t)pixel_value;
        }
    }
   
    if (errors > 0) {
        printf("   [C] AVISO: %d erros durante leitura da janela\n", errors);
    } else {
        printf("   [C] Janela lida com sucesso (%d pixels)\n", buffer_index);
    }
   
    return (errors > 0) ? -1 : 0;
}

/**
 * @brief Prints a matrix of pixel values to console
 */
void print_matrix(const uint8_t *data, int width, int height) {
    if (!data) {
        printf("ERRO: Dados nulos em print_matrix\n");
        return;
    }
   
    printf("\n=== MATRIZ %dx%d ===\n", width, height);
   
    /* Limit display size for readability */
    int max_rows = (height > 20) ? 20 : height;
    int max_cols = (width > 40) ? 40 : width;
   
    if (height > max_rows || width > max_cols) {
        printf("(Mostrando apenas %dx%d da matriz completa)\n\n", max_cols, max_rows);
    }
   
    /* Print column headers */
    printf("     ");
    for (int col = 0; col < max_cols; col++) {
        printf("%3d ", col);
    }
    if (width > max_cols) printf("...");
    printf("\n");
   
    printf("     ");
    for (int col = 0; col < max_cols; col++) {
        printf("----");
    }
    if (width > max_cols) printf("---");
    printf("\n");
   
    /* Print matrix data */
    for (int row = 0; row < max_rows; row++) {
        printf("%3d |", row);
       
        for (int col = 0; col < max_cols; col++) {
            int index = row * width + col;
            printf("%3d ", data[index]);
        }
       
        if (width > max_cols) printf("...");
        printf("\n");
    }
   
    if (height > max_rows) {
        printf("     ...\n");
    }
   
    printf("\n");
}

/* ===================================================================
 * MENU SYSTEM
 * =================================================================== */

/**
 * @brief Displays the interactive menu
 */
void display_menu(int image_loaded, int image_sent_to_fpga) {
    printf("\n\n=== MENU DE TESTE DA API ===\n");
    printf("ESTADO: Buffer C [%s] | FPGA VRAM [%s]\n",
           image_loaded ? "CARREGADA" : "VAZIA",
           image_sent_to_fpga ? "CARREGADA" : "VAZIA");
    printf("----------------------------------------------------------\n");
   
    printf("\n--- Carga de Imagem (Buffer C) ---\n");
    printf(" 1. Carregar Imagem BMP\n");
    printf(" 2. Gerar Gradiente\n");
    printf(" 3. Ler janela da FPGA e exibir matriz\n");
   
    printf("\n--- Algoritmos de Processamento (FPGA) ---\n");
    printf(" 4. Nearest Neighbor (Zoom IN)\n");
    printf(" 5. Pixel Replication (Zoom IN)\n");
    printf(" 6. Decimation (Zoom OUT)\n");
    printf(" 7. Block Averaging (Zoom OUT)\n");
    printf(" 8. Reset\n");
   
    printf("\n----------------------------------------------------------\n");
    printf(" 0. Encerrar API e Sair\n");
   
    printf("\nEscolha uma opcao: ");
}

/**
 * @brief Checks if window reading is allowed based on zoom state
 * @param zoom_level Current zoom level
 * @return 1 if allowed, 0 if not allowed
 */
int can_read_window(int zoom_level) {
    /* Allow reading only if:
     * 1. No zoom operations yet (zoom_level == 0)
     * 2. Only zoom-out operations used (zoom_level < 0)
     * 3. Returned to initial state after zoom operations (zoom_level == 0)
     */
    return (zoom_level <= 0);
}

/* ===================================================================
 * MAIN PROGRAM
 * =================================================================== */
int main(void) {
    /* System state variables */
    int image_loaded_in_memory = 0;
    int image_sent_to_fpga = 0;
    int zoom_level = 0;
   
    int option;
    char filename[256];

    /* Allocate image buffer */
    uint8_t *image_data = malloc(IMG_WIDTH * IMG_HEIGHT);
    if (!image_data) {
        printf("ERRO FATAL: Nao foi possivel alocar memoria para a imagem!\n");
        return 1;
    }

    /* ===================================================================
     * AUTOMATIC INITIALIZATION
     * =================================================================== */
    printf("=== INICIALIZANDO SISTEMA ===\n");
    printf("Inicializando API (API_initialize)...\n");
    
    void *init_result = API_initialize();
    if (init_result == (void*)-1 || init_result == (void*)-2) {
        printf("ERRO FATAL: API_initialize falhou. Verifique o sudo e o mmap.\n");
        free(image_data);
        return -1;
    }
    
    printf(">>> API inicializada com sucesso.\n");
    
    /* Reset FPGA to ensure clean state */
    printf("Executando reset inicial do FPGA...\n");
    ASM_Reset();
    ASM_Pulse_Enable();
    usleep(PULSE_DELAY_US);
    
    printf(">>> Sistema inicializado e pronto para uso.\n");
    wait_for_enter();

    /* ===================================================================
     * MAIN MENU LOOP
     * =================================================================== */
    while (1) {
        display_menu(image_loaded_in_memory, image_sent_to_fpga);
       
        if (scanf("%d", &option) != 1) {
            clear_input_buffer();
            printf("Erro: Entrada invalida. Por favor, digite um numero.\n");
            wait_for_enter();
            continue;
        }

        printf("\n");

        switch (option) {
            /* ==================== LOAD BMP IMAGE ==================== */
            case 1: {
                printf("=== CARREGANDO IMAGEM BMP ===\n");
                printf("Digite o nome do arquivo BMP: ");
                scanf("%255s", filename);
               
                if (load_bmp(filename, image_data) == 0) {
                    printf(">>> SUCESSO: Imagem BMP carregada no buffer C.\n");
                    image_loaded_in_memory = 1;
                    image_sent_to_fpga = 0;
                   
                    /* Check if reset is needed */
                    if (ASM_Get_Flag_Min_Zoom() == 1) {
                        printf("AVISO: Flag Min_Zoom ativa. Considere fazer Reset.\n");
                    }
                   
                    /* Send image to FPGA */
                    printf("=== ENVIANDO IMAGEM PARA FPGA ===\n");
                    if (send_image_to_fpga(image_data) == 0) {
                        printf(">>> SUCESSO: Imagem enviada para a VRAM do FPGA.\n");
                        image_sent_to_fpga = 1;
                        zoom_level = 0;
                    } else {
                        printf("ERRO FATAL: Falha ao enviar imagem para o FPGA.\n");
                        goto cleanup_error;
                    }
                } else {
                    printf("ERRO: Nao foi possivel carregar o BMP.\n");
                }
                break;
            }

            /* ==================== GENERATE TEST PATTERN ==================== */
            case 2: {
                printf("=== GERANDO GRADIENTE ===\n");
                generate_test_pattern(image_data);
                printf(">>> SUCESSO: Gradiente gerado no buffer C.\n");
                image_loaded_in_memory = 1;
                image_sent_to_fpga = 0;
               
                /* Check if reset is needed */
                if (ASM_Get_Flag_Min_Zoom() == 1) {
                    printf("AVISO: Flag Min_Zoom ativa. Considere fazer Reset.\n");
                }
               
                /* Send pattern to FPGA */
                printf("=== ENVIANDO IMAGEM PARA FPGA ===\n");
                if (send_image_to_fpga(image_data) == 0) {
                    printf(">>> SUCESSO: Imagem enviada para a VRAM do FPGA.\n");
                    image_sent_to_fpga = 1;
                    zoom_level = 0;
                } else {
                    printf("ERRO FATAL: Falha ao enviar imagem para o FPGA.\n");
                    goto cleanup_error;
                }
                break;
            }

            /* ==================== READ FPGA WINDOW ==================== */
            case 3: {
                if (!image_sent_to_fpga) {
                    printf("ERRO: Nenhuma imagem na VRAM do FPGA. Carregue uma imagem primeiro (Opcao 1 ou 2).\n");
                    break;
                }

                /* Check if reading is allowed based on zoom state */
                if (!can_read_window(zoom_level)) {
                    printf("ERRO: Nao e possivel ler a janela no estado atual de zoom.\n");
                    printf("   A leitura so e permitida quando:\n");
                    printf("   - Nenhum algoritmo foi executado ainda\n");
                    printf("   - Apenas algoritmos de zoom-out foram usados\n");
                    printf("   - A imagem retornou ao estado inicial apos zoom\n");
                    printf("   Nivel de zoom atual: %d (deve ser <= 0)\n", zoom_level);
                    break;
                }

                printf("\n=== LER VRAM E PRINTAR MATRIZ ===\n");
               
                int x1, y1, x2, y2;
                int rect_x, rect_y, rect_width, rect_height;
               
                printf("Digite a primeira coordenada (x1 y1): ");
                if (scanf("%d %d", &x1, &y1) != 2) {
                    clear_input_buffer();
                    printf("Erro na entrada.\n");
                    break;
                }
               
                printf("Digite a segunda coordenada (x2 y2): ");
                if (scanf("%d %d", &x2, &y2) != 2) {
                    clear_input_buffer();
                    printf("Erro na entrada.\n");
                    break;
                }

                /* Calculate rectangle boundaries */
                rect_x = (x1 < x2) ? x1 : x2;
                rect_y = (y1 < y2) ? y1 : y2;
                rect_width = abs(x2 - x1);
                rect_height = abs(y2 - y1);

                /* Validate rectangle */
                if (rect_width == 0 || rect_height == 0) {
                    printf("ERRO: Area selecionada e vazia.\n");
                    break;
                }

                if (rect_x < 0 || rect_y < 0 || 
                    (rect_x + rect_width > IMG_WIDTH) || 
                    (rect_y + rect_height > IMG_HEIGHT)) {
                    printf("ERRO: Coordenadas fora dos limites da imagem (%dx%d).\n",
                           IMG_WIDTH, IMG_HEIGHT);
                    printf("      Area calculada: Inicio(%d,%d) Tamanho[%dx%d]\n", 
                           rect_x, rect_y, rect_width, rect_height);
                    break;
                }

                /* Allocate and read window */
                uint8_t *window_buffer = (uint8_t*)malloc(rect_width * rect_height);
                if (!window_buffer) {
                    printf("ERRO: Memoria insuficiente.\n");
                    break;
                }

                if (read_fpga_window(window_buffer, rect_x, rect_y, rect_width, rect_height) == 0) {
                    printf(">>> SUCESSO: Dados lidos da area (%d,%d) a (%d,%d).\n",
                           rect_x, rect_y, rect_x + rect_width, rect_y + rect_height);
                    print_matrix(window_buffer, rect_width, rect_height);
                } else {
                    printf("ERRO: Falha na leitura da FPGA.\n");
                }

                free(window_buffer);
                break;
            }

            /* ==================== ZOOM IN: NEAREST NEIGHBOR ==================== */
            case 4:
            /* ==================== ZOOM IN: PIXEL REPLICATION ==================== */
            case 5: {
                if (!image_sent_to_fpga) {
                    printf("ERRO: Nenhuma imagem na VRAM do FPGA. Carregue uma imagem primeiro (Opcao 1 ou 2).\n");
                    break;
                }

                /* Check zoom level constraints */
                if (zoom_level >= MAX_ZOOM_IN_LEVEL) {
                    printf("ERRO: Nivel maximo de Zoom IN atingido (nivel %d).\n", zoom_level);
                    printf("   Nao e possivel executar mais algoritmos de Zoom IN.\n");
                    printf("   Tente um 'Zoom OUT' (6, 7) ou 'Reset' (8).\n");
                    break;
                }
                
                /* Check hardware flag */
                if (ASM_Get_Flag_Max_Zoom() == 1) {
                    printf("ERRO: A 'Flag de Uso Maximo' (Max_Zoom) esta ATIVA.\n");
                    printf("   Nao e possivel executar mais algoritmos de Zoom IN.\n");
                    printf("   Tente um 'Zoom OUT' (6, 7) ou 'Reset' (8).\n");
                    break;
                }
               
                printf("=== EXECUTANDO ALGORITMO (Zoom IN) ===\n");
                int result;
                if (option == 4) {
                    result = execute_algorithm("NearestNeighbor", &NearestNeighbor);
                } else {
                    result = execute_algorithm("PixelReplication", &PixelReplication);
                }
               
                if (result == 0) {
                    zoom_level++;
                    printf("   Nivel de zoom atual: %d\n", zoom_level);
                } else {
                    printf("ERRO FATAL: Falha na execucao do algoritmo.\n");
                    goto cleanup_error;
                }
                break;
            }

            /* ==================== ZOOM OUT: DECIMATION ==================== */
            case 6:
            /* ==================== ZOOM OUT: BLOCK AVERAGING ==================== */
            case 7: {
                if (!image_sent_to_fpga) {
                    printf("ERRO: Nenhuma imagem na VRAM do FPGA. Carregue uma imagem primeiro (Opcao 1 ou 2).\n");
                    break;
                }

                /* Check zoom level constraints */
                if (zoom_level <= MIN_ZOOM_OUT_LEVEL) {
                    printf("ERRO: Nivel minimo de Zoom OUT atingido (nivel %d).\n", zoom_level);
                    printf("   Nao e possivel executar mais algoritmos de Zoom OUT.\n");
                    printf("   Tente um 'Zoom IN' (4, 5) ou 'Reset' (8).\n");
                    break;
                }
                
                /* Check hardware flag */
                if (ASM_Get_Flag_Min_Zoom() == 1) {
                    printf("ERRO: A 'Flag de Zoom Minimo' (Min_Zoom) esta ATIVA.\n");
                    printf("   Nao e possivel executar mais algoritmos de Zoom OUT.\n");
                    printf("   Tente um 'Zoom IN' (4, 5) ou 'Reset' (8).\n");
                    break;
                }

                printf("=== EXECUTANDO ALGORITMO (Zoom OUT) ===\n");
                int result;
                if (option == 6) {
                    result = execute_algorithm("Decimation", &Decimation);
                } else {
                    result = execute_algorithm("BlockAveraging", &BlockAveraging);
                }
               
                if (result == 0) {
                    zoom_level--;
                    printf("   Nivel de zoom atual: %d\n", zoom_level);
                } else {
                    printf("ERRO FATAL: Falha na execucao do algoritmo.\n");
                    goto cleanup_error;
                }
                break;
            }

            /* ==================== RESET ==================== */
            case 8: {
                printf("=== EXECUTANDO: RESET ===\n");
                ASM_Reset();
                zoom_level = 0;
                ASM_Pulse_Enable();
                usleep(PULSE_DELAY_US);
                printf("   [C] Reset concluido. Flags zeradas.\n");
                printf("   Nivel de zoom resetado para: %d\n", zoom_level);
                break;
            }

            /* ==================== EXIT ==================== */
            case 0: {
                printf("=== ENCERRANDO SISTEMA ===\n");
                printf("Encerrando API...\n");
                API_close();
                free(image_data);
                printf("Sistema encerrado com sucesso.\n");
                return 0;
            }

            default:
                printf("ERRO: Opcao invalida. Tente novamente.\n");
                break;
        }

        wait_for_enter();
    }

cleanup_error:
    printf("\n!!! OCORREU UM ERRO FATAL. ENCERRANDO API. !!!\n");
    API_close();
    free(image_data);
    return -1;
}