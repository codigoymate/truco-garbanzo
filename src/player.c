#include <player.h>
#include <stdlib.h>
#include <string_utils.h>

Player *player_new(const char *name) {
	Player *player = (Player *) malloc(sizeof(Player));
	player->name = string_set(NULL, name);

	return player;
}

void player_clear(Player *player) {
	string_clear(player->name);
	free(player);
}

