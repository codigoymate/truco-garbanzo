#include <player.h>
#include <stdlib.h>
#include <string_utils.h>

Player *player_new(const char *name) {
	int i;
	static int id = 0;
	Player *player = (Player *) malloc(sizeof(Player));

	player->name = string_set(NULL, name);
	player->id = id ++; 
	player->next = NULL;

	for (i = 0; i < 3; i ++) {
		player->hand[i] = NULL;
		player->played[i] = NULL;
	}

	return player;
}
