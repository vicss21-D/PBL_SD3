#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#define MAX_FILES 32
#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)

// Macros auxiliares para testar bits (verificar se uma tecla/funcionalidade existe)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array)    ((array[LONG(bit)] >> OFF(bit)) & 1)

// Estrutura para manter o estado do "cursor virtual"
typedef struct {
    int x;
    int y;
} Cursor;

// Função para verificar se o dispositivo tem teclas de teclado (ex: Tecla A)
int is_keyboard(int fd) {
    unsigned long keybit[NBITS(KEY_MAX)];
    // Pede ao kernel os bits de teclas suportadas
    if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybit)), keybit) < 0) return 0;
    
    // Verifica se tem a tecla 'KEY_A' (código 30). Se tiver, provavelmente é um teclado.
    return test_bit(KEY_A, keybit);
}

// Função para verificar se é um mouse (tem movimento relativo e botão esquerdo)
int is_mouse(int fd) {
    unsigned long relbit[NBITS(REL_MAX)];
    unsigned long keybit[NBITS(KEY_MAX)];

    if (ioctl(fd, EVIOCGBIT(EV_REL, sizeof(relbit)), relbit) < 0) return 0;
    if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybit)), keybit) < 0) return 0;

    // Verifica se suporta eixo X relativo E botão esquerdo
    return test_bit(REL_X, relbit) && test_bit(BTN_LEFT, keybit);
}

int main() {
    struct dirent **namelist;
    int n;
    char filename[64];
    int mouse_fd = -1;
    
    printf("--- Varrendo dispositivos em /dev/input/ ---\n");

    // 1. Escaneia o diretório
    n = scandir("/dev/input", &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        return EXIT_FAILURE;
    }

    // 2. Itera sobre os arquivos
    while (n--) {
        // Filtra apenas arquivos que começam com "event"
        if (strncmp(namelist[n]->d_name, "event", 5) == 0) {
            snprintf(filename, sizeof(filename), "/dev/input/%s", namelist[n]->d_name);
            
            int fd = open(filename, O_RDONLY);
            if (fd >= 0) {
                char name[256] = "Desconhecido";
                ioctl(fd, EVIOCGNAME(sizeof(name)), name);

                if (is_keyboard(fd)) {
                    printf("[TECLADO ENCONTRADO]: %s (%s)\n", name, filename);
                } 
                else if (is_mouse(fd)) {
                    printf("[MOUSE ENCONTRADO]  : %s (%s)\n", name, filename);
                    // Se ainda não selecionamos um mouse, pega este.
                    if (mouse_fd == -1) {
                        mouse_fd = fd; // Mantém aberto para leitura
                        printf(">>> Selecionado para captura!\n");
                    } else {
                        close(fd);
                    }
                } else {
                    close(fd);
                }
            }
        }
        free(namelist[n]);
    }
    free(namelist);

    if (mouse_fd == -1) {
        printf("Nenhum mouse detectado.\n");
        return EXIT_FAILURE;
    }

    // 3. Lógica de Captura e "Cálculo de Coordenadas"
    printf("\n--- Iniciando captura no Mouse selecionado ---\n");
    printf("Nota: As coordenadas iniciam em (0,0). Mova o mouse.\n");

    struct input_event ev;
    Cursor cursor = {0, 0}; // Começa em 0,0 pois não sabemos onde o X11 está.

    while (read(mouse_fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_KEY) {
            printf("Botão: %s %s\n", 
                (ev.code == BTN_LEFT) ? "ESQUERDO" : 
                (ev.code == BTN_RIGHT) ? "DIREITO" : "OUTRO",
                (ev.value) ? "Pressionado" : "Solto");
        } 
        else if (ev.type == EV_REL) {
            // AQUI ESTÁ O TRUQUE DAS COORDENADAS
            // Somamos o deslocamento (delta) à posição atual
            if (ev.code == REL_X) {
                cursor.x += ev.value;
            } else if (ev.code == REL_Y) {
                cursor.y += ev.value;
            }
            // Geralmente se imprime apenas quando ocorre um evento de sincronização (EV_SYN),
            // mas para simplificar, imprimiremos a cada movimento.
            printf("Posição Virtual (X, Y): (%d, %d) | Delta: %+d\n", cursor.x, cursor.y, ev.value);
        }
    }

    close(mouse_fd);
    return 0;
}