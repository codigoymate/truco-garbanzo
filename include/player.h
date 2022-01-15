#ifndef PLAYER_H
#define PLAYER_H

#include <card.h>

typedef struct Player {
	char *name;
	int id, tx, ty, score;
	Card *hand[3], *played[3];

	struct Player *next;
} Player;

Player *player_new(const char *name);

#endif

