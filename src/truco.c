#include <truco.h>
#include <malloc.h>
#include <stdlib.h>
#include <string_utils.h>
#include <deck.h>

Truco *truco_new(void) {
	Truco *truco = (Truco *) malloc(sizeof(Truco));
	truco->quit = 0;
	truco->stage = MAIN_MENU_STAGE;
	truco->first_player = NULL;
	truco->last_player = NULL;
	truco->current_player = 0;
	deck_init(truco->deck);
	return truco;
}

void truco_clean(Truco *truco) {
	clean_players(truco);
	deck_clean(truco->deck);
	free(truco);
}

void add_player(Truco *truco, const char *name) {
	Player *player = (Player *) malloc(sizeof(Player));
	player->name = string_set(NULL, name);
	player->next = NULL;

	if (truco->last_player == NULL) {
		truco->last_player = player;
		truco->first_player = player;
	} else {
		truco->last_player->next = player;
		truco->last_player = player;
	}
}

void clean_players(Truco *truco) {
	Player *next;
	Player *player = truco->first_player;

	while (player) {
		next = player->next;
		string_clear(player->name);
		free(player);
		player = next;
	}

	truco->first_player = NULL;
	truco->last_player = NULL;
}

Player *get_player(Truco *truco, int index) {
	Player *player = truco->first_player;
	int i = 0;

	while (player) {
		if (i == index) return player;
		player = player->next;
		i ++;
	}

	return NULL;
}


void start_game(Truco *truco) {
	// Clear existing players
	clean_players(truco);

	// Create players
	add_player(truco, getenv("USER"));
	add_player(truco, "Pepe");

	if (truco->playerCount > 2) {
		add_player(truco, "María");
		add_player(truco, "Pablo");
	}

	if (truco->playerCount > 4) {
		add_player(truco, "Franco");
		add_player(truco, "Pamela");
	}

	switch (truco->playerCount) {
	case 2:
		get_player(truco, 0)->tx = 40;
		get_player(truco, 0)->ty = 25;
		get_player(truco, 1)->tx = 40;
		get_player(truco, 1)->ty = 5;
		break;
	case 4:
		get_player(truco, 0)->tx = 40;
		get_player(truco, 0)->ty = 25;
		get_player(truco, 1)->tx = 20;
		get_player(truco, 1)->ty = 15;
		get_player(truco, 2)->tx = 40;
		get_player(truco, 2)->ty = 5;
		get_player(truco, 3)->tx = 60;
		get_player(truco, 3)->ty = 15;
		break;

	case 6:
		get_player(truco, 0)->tx = 40;
		get_player(truco, 0)->ty = 25;

		get_player(truco, 1)->tx = 20;
		get_player(truco, 1)->ty = 20;

		get_player(truco, 2)->tx = 20;
		get_player(truco, 2)->ty = 10;

		get_player(truco, 3)->tx = 40;
		get_player(truco, 3)->ty = 5;

		get_player(truco, 4)->tx = 60;
		get_player(truco, 4)->ty = 10;

		get_player(truco, 5)->tx = 60;
		get_player(truco, 5)->ty = 20;

		break;
	
	default:
		break;
	}

}
