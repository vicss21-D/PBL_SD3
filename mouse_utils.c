#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#include "mouse_utils.h"

// Tamanho máximo do buffer de caminho/nome
#define MAX_PATH_LEN 256

/*
 * --- FUNÇÕES DE UTILITY DE DISPOSITIVO (is_mouse) ---
 */

// Implementação da função para verificar se o dispositivo é um mouse
int is_mouse(int fd) {
    unsigned long relbit[NBITS(REL_MAX)];
    unsigned long keybit[NBITS(KEY_MAX)];

    if (ioctl(fd, EVIOCGBIT(EV_REL, sizeof(relbit)), relbit) < 0) return 0;
    if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybit)), keybit) < 0) return 0;

    // Verifica se suporta eixo X relativo E botão esquerdo
    return test_bit(REL_X, relbit) && test_bit(BTN_LEFT, keybit);
}


/*
 * --- FUNÇÃO 1: VARREDURA E ABERTURA (find_and_open_mouse) ---
 */

int find_and_open_mouse(char *device_path_out, char *name_out) {
    struct dirent **namelist;
    int n;
    int mouse_fd = -1;
    
    printf("Varrendo dispositivos em /dev/input/...\n");

    n = scandir("/dev/input", &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        return -1;
    }

    while (n--) {
        if (strncmp(namelist[n]->d_name, "event", 5) == 0) {
            char filename[MAX_PATH_LEN];
            snprintf(filename, MAX_PATH_LEN, "/dev/input/%s", namelist[n]->d_name);
            
            int fd = open(filename, O_RDONLY);
            if (fd >= 0) {
                char name[MAX_PATH_LEN] = "Desconhecido";
                ioctl(fd, EVIOCGNAME(sizeof(name)), name);

                if (is_mouse(fd)) {
                    printf("[MOUSE ENCONTRADO]  : %s (%s)\n", name, filename);
                    if (mouse_fd == -1) {
                        mouse_fd = fd; // Mantém aberto para retorno
                        
                        // Armazena as informações para o programa chamador
                        strncpy(device_path_out, filename, MAX_PATH_LEN);
                        strncpy(name_out, name, MAX_PATH_LEN);

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

    return mouse_fd;
}


/*
 * --- FUNÇÃO 2: LEITURA E PROCESSAMENTO DE EVENTOS (read_and_process_mouse_event) ---
 */

int read_and_process_mouse_event(int mouse_fd, Cursor *current_cursor, MouseEvent *event_out) {
    struct input_event ev;
    ssize_t bytes_read = read(mouse_fd, &ev, sizeof(ev));

    if (bytes_read == 0) {
        // EOF
        return 0; 
    }
    if (bytes_read == -1) {
        perror("Erro ao ler o evento do mouse");
        return -1;
    }
    if (bytes_read != sizeof(ev)) {
        // Leitura parcial, ignorar
        return 1; 
    }

    // Preenche a estrutura de saída
    event_out->event_type = ev.type;
    event_out->event_code = ev.code;
    event_out->event_value = ev.value;
    
    // Processamento do movimento para atualizar o cursor
    if (ev.type == EV_REL) {
        if (ev.code == REL_X) {
            current_cursor->x += ev.value;
        } else if (ev.code == REL_Y) {
            current_cursor->y += ev.value;
        }
    }
    
    // Copia a posição atualizada para a saída
    event_out->cursor_pos = *current_cursor;

    // Retorna 1 para indicar que um evento foi lido e processado
    return 1;
}