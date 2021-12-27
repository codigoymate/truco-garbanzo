#ifndef CARD_H
#define CARD_H

#define ORO				0
#define COPAS			1
#define ESPADAS			2
#define BASTOS			3

typedef struct {
	int value, type, power, envido;
} Card;

Card *card_new(int value, int type, int pow, int envido);

#endif
