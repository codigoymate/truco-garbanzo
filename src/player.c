#include <player.h>
#include <stdlib.h>
#include <string_utils.h>

Player *player_new(const char *name) {
	int i;
	Player *player = (Player *) malloc(sizeof(Player));

	player->name = string_set(NULL, name);
	player->next = NULL;

	for (i = 0; i < 3; i ++) {
		player->hand[i] = NULL;
		player->played[i] = NULL;
	}

	return player;
}
