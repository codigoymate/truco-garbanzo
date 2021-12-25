#include <truco.h>
#include <malloc.h>
#include <stdlib.h>

Truco *truco;

void clean_players(void) {
	int i;
	for (i = 0; i < MAX_PLAYERS; i ++) {
		if (truco->players[i]) {
			player_clear(truco->players[i]);
		}
	}
}

Truco *truco_new(void) {
	Truco *truco = (Truco *) malloc(sizeof(truco));
	truco->quit = 0;
	truco->stage = MAIN_MENU_STAGE;
	return truco;
}

void truco_clean(Truco *truco) {
	//clean_players();
	free(truco);
}

void start_game(Truco *truco) {
	// Clear existing players
	//clean_players();

	// Create players
	truco->players[0] = player_new(getenv("USER"));
	truco->players[1] = player_new("Pepe");

	if (truco->playerCount > 2) {
		truco->players[2] = player_new("María");
		truco->players[3] = player_new("Pablo");
	}

	if (truco->playerCount > 4) {
		truco->players[4] = player_new("Franco");
		truco->players[5] = player_new("Pamela");
	}

}
