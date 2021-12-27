#include <card.h>
#include <stdlib.h>

Card *card_new(int value, int type, int pow, int envido) {
	Card *card = (Card *) malloc(sizeof(Card));
	card->value = value;
	card->type = type;
	card->power = pow;
	card->envido = envido;

	return card;
}