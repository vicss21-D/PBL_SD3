/*
 * =========================================================================
 * mouse_utils.h: Mouse Input Utilities Header
 * =========================================================================
 *
 * Provides mouse device detection, opening, and event processing
 * for Linux input subsystem (/dev/input/eventX)
 *
 */

#ifndef MOUSE_UTILS_H
#define MOUSE_UTILS_H

#include <linux/input.h>
#include <stdint.h>

/* ===================================================================
 * BIT MANIPULATION MACROS
 * =================================================================== */
#define NBITS(x) ((((x) - 1) / (sizeof(long) * 8)) + 1)
#define test_bit(bit, array) ((array[(bit) / (sizeof(long) * 8)] >> ((bit) % (sizeof(long) * 8))) & 1)

/* ===================================================================
 * DATA STRUCTURES
 * =================================================================== */

/**
 * @brief Virtual cursor position
 */
typedef struct {
    int x;
    int y;
} Cursor;

/**
 * @brief Mouse event with cursor position
 */
typedef struct {
    uint16_t event_type;   // Event type (EV_REL, EV_KEY, etc.)
    uint16_t event_code;   // Event code (REL_X, BTN_LEFT, etc.)
    int32_t  event_value;  // Event value
    Cursor   cursor_pos;   // Current cursor position after processing
} MouseEvent;

/* ===================================================================
 * FUNCTION PROTOTYPES
 * =================================================================== */

/**
 * @brief Checks if a device file descriptor is a mouse
 * @param fd File descriptor of the device
 * @return 1 if device is a mouse, 0 otherwise
 */
int is_mouse(int fd);

/**
 * @brief Finds and opens the first available mouse device
 * @param device_path_out Output buffer for device path (size >= 256)
 * @param name_out Output buffer for device name (size >= 256)
 * @return File descriptor on success, -1 on failure
 */
int find_and_open_mouse(char *device_path_out, char *name_out);

/**
 * @brief Reads and processes a mouse event
 * @param mouse_fd Mouse device file descriptor
 * @param current_cursor Pointer to current cursor state (updated by function)
 * @param event_out Output structure for event data
 * @return 1 on success, 0 on EOF, -1 on error
 */
int read_and_process_mouse_event(int mouse_fd, Cursor *current_cursor, MouseEvent *event_out);

#endif /* MOUSE_UTILS_H */
