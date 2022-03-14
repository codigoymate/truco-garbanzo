#ifndef CARD_H
#define CARD_H

#include <ncurses.h>

#define ORO				0
#define COPAS			1
#define ESPADAS			2
#define BASTOS			3

typedef struct {
	int value, type, power;
} Card;

/**
 * @brief Create a new card.
 * 
 * @param value 1 to 7 and 10 to 12.
 * @param type ORO, COPAS, ESPADAS, BASTOS.
 * @param pow 0 (4 OCEB) to 13 (1 E)
 * @return Card* card pointer.
 */
Card *card_new(int value, int type, int pow);

/**
 * @brief Generate long name string. ex:
 * - 4B ->  "el 4 de bastos".
 * - 10C -> "la sota de copas".
 * - 1E ->  "el ancho de espadas".
 * 
 * Note: string requires destroy after.
 * 
 * @param card card instance.
 * @return char* the string name.
 */
char *card_long_name(Card *card);

/**
 * @brief Generate short name string.
 * Ex: 4B, 6C, 10O
 * 
 * Note: string requires destroy after.
 * 
 * @param card card instance.
 * @return char* the string name.
 */
char *card_short_name(Card *card);

/**
 * @brief Draw normal card on window at position x, y
 * 
 * @param wnd WINDOW to draw the card.
 * @param card card instace.
 * @param x x position
 * @param y y position
 */
void card_draw(WINDOW *wnd, Card *card, int x, int y);

/**
 * @brief Draw small card on window at position x, y
 * 
 * @param wnd WINDOW to draw the card.
 * @param card card instace.
 * @param x x position
 * @param y y position
 */
void card_draw_small(WINDOW *wnd, Card *card, int x, int y);

#endif
