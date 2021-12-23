#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
	char *name;
} Player;

#endif

Player *player_new(const char *name);
void player_clear(Player *player);
