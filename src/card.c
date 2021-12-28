#include <card.h>
#include <stdlib.h>
#include <string_utils.h>
#include <stdio.h>

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
	//char *name = card_short_name(card);
	int w = 10, h = 6, i, j; 

	wattron(wnd, COLOR_PAIR(3));

	// Background
	for (j = y; j < y + h; j ++)
		for (i = x; i < x + w; i ++)
			mvwaddch(wnd, j, i, ' ');

	// Border
	rectangle(wnd, x, y, w, h);

	// Values
	mvwprintw(wnd, y + 1, x + 1, "%d", card->value);

	wattroff(wnd, COLOR_PAIR(3));

	switch (card->type) {
	case ORO:
		wattron(wnd, COLOR_PAIR(4));
		mvwaddch(wnd, y + 2, x + 1, 'O');
		wattroff(wnd, COLOR_PAIR(4));
		break;
	case COPAS:
		wattron(wnd, COLOR_PAIR(5));
		mvwaddch(wnd, y + 2, x + 1, 'C');
		wattroff(wnd, COLOR_PAIR(5));
		break;
	case ESPADAS:
		wattron(wnd, COLOR_PAIR(6));
		mvwaddch(wnd, y + 2, x + 1, 'E');
		wattroff(wnd, COLOR_PAIR(6));
		break;
	case BASTOS:
		wattron(wnd, COLOR_PAIR(7));
		mvwaddch(wnd, y + 2, x + 1, 'B');
		wattroff(wnd, COLOR_PAIR(7));
		break;
	}

	//string_clear(name);
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