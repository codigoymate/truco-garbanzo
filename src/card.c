#include <card.h>
#include <stdlib.h>
#include <string_utils.h>
#include <stdio.h>

#include <colors.h>

void draw_coin(WINDOW *wnd, int x, int y);
void draw_cup(WINDOW *wnd, int x, int y);

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
	case 1: name = string_set(name, "ancho"); break;
	case 10: name = string_set(name, "sota"); break;
	case 11: name = string_set(name, "caballo"); break;
	case 12: name = string_set(name, "rey"); break;
	default: {
		char val[] = {card->value + 48, '\0'};
		name = string_set(name, val);
		}
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
		wattron(wnd, COLOR_PAIR(PAIR_CARD_ESPADAS));
		mvwaddch(wnd, y + 2, x + 1, 'E');
		wattroff(wnd, COLOR_PAIR(PAIR_CARD_ESPADAS));
		break;
	case BASTOS:
		wattron(wnd, COLOR_PAIR(PAIR_CARD_BASTOS));
		mvwaddch(wnd, y + 2, x + 1, 'B');
		wattroff(wnd, COLOR_PAIR(PAIR_CARD_BASTOS));
		break;
	}

	wattron(wnd, COLOR_PAIR(PAIR_CARD));

	// Values
	mvwprintw(wnd, y + 1, x + 1, "%d", card->value);

	wattroff(wnd, COLOR_PAIR(PAIR_CARD));
}

void rectangle(WINDOW *wnd, int x, int y, int w, int h) {
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
5257580, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257579, 5257592, 1063200, 1063200, 1055008, 4201080, 4201080, 
1055008, 1063200, 1063200, 5257592, 5257592, 1063200, 4201073, 6688, 4201056, 4201056, 6688, 4201073, 1063200, 5257592, 5257592, 1063200, 
4201073, 6688, 4201056, 4201056, 6688, 4201073, 1063200, 5257592, 5257592, 1063200, 1063200, 1055008, 4201080, 4201080, 1055008, 1063200, 
1063200, 5257592, 5257581, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257578	};

	for (yy = 0; yy < h; yy ++)
		for (xx = 0; xx < w; xx ++) {
			if (m[i]) mvwaddch(wnd, yy + y, xx + x, m[i]);
			i ++;
		}
	
}

void draw_cup(WINDOW *wnd, int x, int y) {
	int w = 10, h = 6, xx, yy, i = 0;
	chtype m[] = {
5257580, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257579, 5257592, 1063200, 2106204, 2106223, 2106223, 2106223, 
2106223, 2106159, 1063200, 5257592, 5257592, 1063200, 1063200, 2106204, 2106223, 2106223, 2106159, 1063200, 1063200, 5257592, 5257592, 1063200, 
1063200, 1063200, 6301304, 6301304, 1063200, 1063200, 1063200, 5257592, 5257592, 1063200, 1063200, 6301297, 6301302, 6301302, 6301297, 1063200, 
1063200, 5257592, 5257581, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257578	};

	for (yy = 0; yy < h; yy ++)
		for (xx = 0; xx < w; xx ++) {
			if (m[i]) mvwaddch(wnd, yy + y, xx + x, m[i]);
			i ++;
		}
}
