/*
 * =========================================================================
 * mouse_utils.h: Header de utilitários do mouse
 * =========================================================================
 *
 * Faz detecção leitura e processamento de eventos pro sistema de input do Linux
 * a partir de dispositivos de mouse.
 *
 */

#ifndef MOUSE_UTILS_H
#define MOUSE_UTILS_H

#include <linux/input.h>
#include <stdint.h>

/* ===================================================================
 * Macros de bits para manipulação 
 * =================================================================== */
#define NBITS(x) ((((x) - 1) / (sizeof(long) * 8)) + 1)
#define test_bit(bit, array) ((array[(bit) / (sizeof(long) * 8)] >> ((bit) % (sizeof(long) * 8))) & 1)

/* ===================================================================
 * Estruturas de Dados
 * =================================================================== */

/**
 * @brief Posição do cursor
 */
typedef struct {
    int x;
    int y;
} Cursor;

/**
 * @brief Evento do mouse com posição do cursor
 */
typedef struct {
    uint16_t event_type;   // Event type (EV_REL, EV_KEY, etc.)
    uint16_t event_code;   // Event code (REL_X, BTN_LEFT, etc.)
    int32_t  event_value;  // Event value
    Cursor   cursor_pos;   // Current cursor position after processing
} MouseEvent;

/* ===================================================================
 * Protótipos das Funções
 * =================================================================== */

/**
 * @brief Verifica se o dispositivo associado ao fd é um mouse
 * @param fd File descriptor do dispositivo
 * @return 1 se for mouse, 0 caso contrário
 */
int is_mouse(int fd);

/**
 * @brief Encontra e abre o dispositivo de mouse
 * @param device_path_out Buffer de saída para o caminho do dispositivo (size >= 256)
 * @param name_out Buffer de saída para o nome do dispositivo (size >= 256)
 * @return File descriptor do mouse aberto, ou -1 se falhar
 */
int find_and_open_mouse(char *device_path_out, char *name_out);

/**
 * @brief Lê e processa um evento do mouse
 * @param mouse_fd File descriptor do mouse
 * @param current_cursor Ponteiro para a posição atual do cursor
 * @param event_out Ponteiro para a estrutura de saída do evento
 * @return 1 se um evento foi lido e processado, 0 para EOF, -1 em caso de erro
 */
int read_and_process_mouse_event(int mouse_fd, Cursor *current_cursor, MouseEvent *event_out);

#endif /* MOUSE_UTILS_H */
