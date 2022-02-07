#ifndef CARD_H
#define CARD_H

#include <ncurses.h>

#define ORO				0
#define COPAS			1
#define ESPADAS			2
#define BASTOS			3

typedef struct {
	int value, type, power, envido;
} Card;

Card *card_new(int value, int type, int pow, int envido);
char *card_long_name(Card *card);
char *card_short_name(Card *card);

void card_draw(WINDOW *wnd, Card *card, int x, int y);
void card_draw_small(WINDOW *wnd, Card *card, int x, int y);

#endif
