#include <card.h>
#include <stdlib.h>
#include <string_utils.h>
#include <stdio.h>

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
		char val[2];
		val[0] = card->value + 48;
		val[1] = '\0';
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
