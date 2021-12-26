#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
	char *name;
	struct Player *next;
} Player;

#endif

