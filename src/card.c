#include <card.h>
#include <stdlib.h>
#include <string_utils.h>
#include <stdio.h>

#include <colors.h>

void draw_coin(WINDOW *wnd, int x, int y);
void draw_cup(WINDOW *wnd, int x, int y);
void draw_spade(WINDOW * wnd, int x, int y);
void draw_stick(WINDOW * wnd, int x, int y);

void rectangle(WINDOW *wnd, int x, int y, int w, int h);

Card *card_new(int value, int type, int pow, int envido) {
	Card *card = (Card *) malloc(sizeof(Card));
	card->value = value;
	card->type = type;
	card->power = pow;
	card->envido = envido;

	return card;
}

char *card_long_name(Card *card) {
	char *name = NULL;

	switch (card->value) {
	case 1: name = string_set(name, "el ancho"); break;
	case 10: name = string_set(name, "la sota"); break;
	case 11: name = string_set(name, "el caballo"); break;
	case 12: name = string_set(name, "el rey"); break;
	default:
		name = string_set(name, "el ");
		name = string_cat_number(name, card->value);
	}

	switch (card->type) {
	case ORO: name = string_cat(name, " de oro"); break;
	case COPAS: name = string_cat(name, " de copas"); break;
	case ESPADAS: name = string_cat(name, " de espadas"); break;
	case BASTOS: name = string_cat(name, " de bastos"); break;
	default: break;
	}

	return name;
}

char *card_short_name(Card *card) {
	char name[] = {"12B"};
	char type;

	switch (card->type) {
	case ORO: type = 'O'; break;
	case COPAS: type = 'C'; break;
	case ESPADAS: type = 'E'; break;
	case BASTOS: type = 'B'; break;
	
	default:
		break;
	}

	sprintf(name, "%d%c", card->value, type);

	return string_set(NULL, name);
}

void card_draw(WINDOW *wnd, Card *card, int x, int y) {

	switch (card->type) {
	case ORO:
		draw_coin(wnd, x, y);
		wattron(wnd, COLOR_PAIR(PAIR_CARD_ORO) | A_ALTCHARSET);
		mvwaddch(wnd, y + 2, x + 1, ACS_DIAMOND);
		wattroff(wnd, COLOR_PAIR(PAIR_CARD_ORO) | A_ALTCHARSET);
		break;
	case COPAS:
		draw_cup(wnd, x, y);
		wattron(wnd, COLOR_PAIR(PAIR_CARD_COPAS));
		mvwaddch(wnd, y + 2, x + 1, 'C');
		wattroff(wnd, COLOR_PAIR(PAIR_CARD_COPAS));
		break;
	case ESPADAS:
		draw_spade(wnd, x, y);
		wattron(wnd, COLOR_PAIR(PAIR_CARD_ESPADAS));
		mvwaddch(wnd, y + 2, x + 1, 'E');
		wattroff(wnd, COLOR_PAIR(PAIR_CARD_ESPADAS));
		break;
	case BASTOS:
		draw_stick(wnd, x, y);
		wattron(wnd, COLOR_PAIR(PAIR_CARD_BASTOS));
		mvwaddch(wnd, y + 2, x + 1, 'B');
		wattroff(wnd, COLOR_PAIR(PAIR_CARD_BASTOS));
		break;
	}

	wattron(wnd, COLOR_PAIR(PAIR_CARD));

	/* Values */
	mvwprintw(wnd, y + 1, x + 1, "%d", card->value);

	wattroff(wnd, COLOR_PAIR(PAIR_CARD));
}

void card_draw_small(WINDOW *wnd, Card *card, int x, int y) {
	wattron(wnd, COLOR_PAIR(PAIR_CARD));
	rectangle(wnd, x, y, 5, 3);
	if (card->value != -1)
		mvwprintw(wnd, y + 1, x + 1, "%d", card->value);
	wattroff(wnd, COLOR_PAIR(PAIR_CARD));

	switch (card->type) {
	case ORO:
		mvwaddch(wnd, y + 2, x + 1, 'O' | COLOR_PAIR(PAIR_CARD_ORO));
		mvwaddch(wnd, y + 2, x + 3, ACS_DIAMOND | COLOR_PAIR(PAIR_CARD_ORO) | A_ALTCHARSET);
		break;
	case COPAS:
		mvwaddch(wnd, y + 2, x + 1, 'C' | COLOR_PAIR(PAIR_CARD_COPAS) | A_DIM);
		mvwaddch(wnd, y + 2, x + 3, 'Y' | COLOR_PAIR(PAIR_CARD_COPAS) | A_DIM);
		break;
	case ESPADAS:
		mvwaddch(wnd, y + 2, x + 1, 'E' | COLOR_PAIR(PAIR_CARD_ESPADAS));
		mvwaddch(wnd, y + 2, x + 3, ACS_PLUS | COLOR_PAIR(PAIR_CARD_ESPADAS) | A_ALTCHARSET);
		break;
	case BASTOS:
		mvwaddch(wnd, y + 2, x + 1, 'B' | COLOR_PAIR(PAIR_CARD_BASTOS));
		mvwaddch(wnd, y + 2, x + 3, '/' | COLOR_PAIR(PAIR_CARD_BASTOS) | A_BOLD);
		break;
	}
}

void rectangle(WINDOW *wnd, int x, int y, int w, int h) {

	int xx, yy;

	for (yy = y; yy < y + h; yy ++)
		for (xx = x; xx < x + w; xx ++)
			mvwaddch(wnd, yy, xx, ' ');

	mvwhline(wnd, y, x, 0, w);
	mvwhline(wnd, y + h, x, 0, w);
	mvwvline(wnd, y, x, 0, h);
	mvwvline(wnd, y, x + w, 0, h);
	mvwaddch(wnd, y, x, ACS_ULCORNER);
    mvwaddch(wnd, y + h, x, ACS_LLCORNER);
    mvwaddch(wnd, y, x + w, ACS_URCORNER);
    mvwaddch(wnd, y + h, x + w, ACS_LRCORNER);
}

void draw_coin(WINDOW *wnd, int x, int y) {
	int w = 10, h = 6, xx, yy, i = 0;
	chtype m[] = {
0x50396C, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x50396B, 0x503978, 0x103920, 0x103920, 0x101920, 0x401A78, 0x401A78, 
0x101920, 0x103920, 0x103920, 0x503978, 0x503978, 0x103920, 0x401A71, 0x1A20, 0x401A60, 0x401A60, 0x1A20, 0x401A71, 0x103920, 0x503978, 0x503978, 0x103920, 
0x401A71, 0x1A20, 0x401A60, 0x401A60, 0x1A20, 0x401A71, 0x103920, 0x503978, 0x503978, 0x103920, 0x103920, 0x101920, 0x401A78, 0x401A78, 0x101920, 0x103920, 
0x103920, 0x503978, 0x50396D, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x50396A	};

	for (yy = 0; yy < h; yy ++)
		for (xx = 0; xx < w; xx ++) {
			if (m[i]) mvwaddch(wnd, yy + y, xx + x, m[i]);
			i ++;
		}
	
}

void draw_cup(WINDOW *wnd, int x, int y) {
	int w = 10, h = 6, xx, yy, i = 0;
	chtype m[] = {
0x50396C, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x50396B, 0x503978, 0x103920, 0x20235C, 0x20236F, 0x20236F, 0x20236F, 
0x20236F, 0x20232F, 0x103920, 0x503978, 0x503978, 0x103920, 0x103920, 0x20235C, 0x20236F, 0x20236F, 0x20232F, 0x103920, 0x103920, 0x503978, 0x503978, 0x103920, 
0x103920, 0x103920, 0x602678, 0x602678, 0x103920, 0x103920, 0x103920, 0x503978, 0x503978, 0x103920, 0x103920, 0x602671, 0x602676, 0x602676, 0x602671, 0x103920, 
0x103920, 0x503978, 0x50396D, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x50396A	};

	for (yy = 0; yy < h; yy ++)
		for (xx = 0; xx < w; xx ++) {
			if (m[i]) mvwaddch(wnd, yy + y, xx + x, m[i]);
			i ++;
		}
}

void draw_spade(WINDOW *wnd, int x, int y) {
	int w = 10, h = 6, xx, yy, i = 0;
	chtype m[] = {
0x50396C, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x50396B, 0x503978, 0x103920, 0x103920, 0x103920, 0x103920, 0x503B6D, 
0x102920, 0x503B6B, 0x103920, 0x503978, 0x503978, 0x103920, 0x103920, 0x103920, 0x103920, 0x20372F, 0x20372F, 0x103920, 0x103920, 0x503978, 0x503978, 0x103920, 
0x103920, 0x103920, 0x20372F, 0x20372F, 0x103920, 0x103920, 0x103920, 0x503978, 0x503978, 0x103920, 0x103920, 0x20372F, 0x20372F, 0x103920, 0x103920, 0x103920, 
0x103920, 0x503978, 0x50396D, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x503971, 0x50396A	};

	for (yy = 0; yy < h; yy ++)
		for (xx = 0; xx < w; xx ++) {
			if (m[i]) mvwaddch(wnd, yy + y, xx + x, m[i]);
			i ++;
		}
}

void draw_stick(WINDOW *wnd, int x, int y) {
	int w = 10, h = 6, xx, yy, i = 0;
	chtype m[] = {
5257580, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257579, 5257592, 1063200, 1063200, 1063200, 1063200, 1063200, 
1063200, 1063200, 1063200, 5257592, 5257592, 1063200, 1063200, 1063200, 1063200, 1063200, 1063200, 1063200, 1063200, 5257592, 5257592, 1063200, 
1063200, 1063200, 1063200, 1063200, 1063200, 1063200, 1063200, 5257592, 5257592, 1063200, 1063200, 1063200, 1063200, 1063200, 1063200, 1063200, 
1063200, 5257592, 5257581, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257578	};

	for (yy = 0; yy < h; yy ++)
		for (xx = 0; xx < w; xx ++) {
			if (m[i]) mvwaddch(wnd, yy + y, xx + x, m[i]);
			i ++;
		}
}
