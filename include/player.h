#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
	char *name;
	int tx, ty;
	struct Player *next;
} Player;

#endif

