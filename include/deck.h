#ifndef DECK_H
#define DECK_H

#include <card.h>
#include <truco.h>

void deck_init(Card *deck[]);
void deck_clean(Card *deck[]);

void deck_merge(Card *deck[]);

/**
 * @brief Deal cards and reset the players.
 * 
 * @param truco Truco instance.
 */
void deal_cards(Truco *truco);

#endif
