#ifndef PLAYER_H
#define PLAYER_H

#include <card.h>

typedef struct Player {
	char *name;
	int id, tx, ty, score, surrendered;
	Card *hand[3], *played[3];

	struct Player *next;
} Player;

Player *player_new(const char *name);

/**
 * @brief The player plays the index card.
 * Move the card from index hand to free space on played array
 * 
 * @param truco Truco instance.
 * @param player The player instance.
 * @param index The hand index.
 * @return int 1 if and only if the operation was successfully.
 */
int play_card(Player *player, int index);

/**
 * @brief Player setted to surrendered mode.
 * 
 * @param player player instance.
 * @param deck for the null card.
 */
void give_up(Player *player, Card *deck[]);

/**
 * @brief Check the cards on player hand and return 1
 * if all cards is less than ases.
 * 
 * @param player Player instance.
 * @return int 1 if and only if cards pawer < 7.
 */
int has_low_cards(Player *player);

#endif

