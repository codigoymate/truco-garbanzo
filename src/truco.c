#include <truco.h>
#include <malloc.h>
#include <stdlib.h>
#include <string_utils.h>

Truco *truco;

Truco *truco_new(void) {
	Truco *truco = (Truco *) malloc(sizeof(truco));
	truco->quit = 0;
	truco->stage = MAIN_MENU_STAGE;
	truco->first_player = NULL;
	truco->last_player = NULL;
	return truco;
}

void truco_clean(Truco *truco) {
	clean_players(truco);
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

}
