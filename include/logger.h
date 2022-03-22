#ifndef LOGGER_H
#define LOGGER_H

#include <card.h>
#include <player.h>

#define LOGGER_LINES        4
#define LOGGER_MAX          40

typedef struct {
    char line[LOGGER_LINES][LOGGER_MAX];
} Logger;

void log_init(void);
void log_clean(void);

void log_print(char *str);
void log_draw(void);

/**
 * @brief Save round status before start.
 * 
 * @param deck List of all merged cards.
 * @param first_player First player instance.
 * @param start_player start player id (mano).
 */
void log_save_round_status(Card *deck[], Player *first_player, int start_player);

#endif
