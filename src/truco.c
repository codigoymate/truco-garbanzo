#include <truco.h>
#include <malloc.h>
#include <stdlib.h>
#include <string_utils.h>
#include <deck.h>

/**
 * @brief Return 1 if the hand n is clear (nobody played)
 * 
 * @param truco truco instance
 * @param n number of hand
 * @return int 1 if n is clear
 */
int is_hand_clear(Truco *truco, int n);

/**
 * @brief Return 1 if the hand n is full (all played)
 * 
 * @param truco truco instance
 * @param n number of hand
 * @return int 1 if n is full
 */
int is_hand_full(Truco *truco, int n);

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

	Player *player = player_new(name);

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
	/* Clear existing players */
	clean_players(truco);

	/* Create players */
	add_player(truco, getenv("USER"));
	add_player(truco, "Pepe");

	if (truco->player_count > 2) {
		add_player(truco, "María");
		add_player(truco, "Pablo");
	}

	if (truco->player_count > 4) {
		add_player(truco, "Franco");
		add_player(truco, "Pamela");
	}

	/* Select the start player */
	truco->start_player = rand() % truco->player_count;

	switch (truco->player_count) {
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

int is_hand_clear(Truco *truco, int n) {
	Player *player;

	for (player = truco->first_player; player; player = player->next) {
		if (player->played[n]) return 0;
	}

	return 1;
}

int is_hand_full(Truco *truco, int n) {
	Player *player;

	for (player = truco->first_player; player; player = player->next) {
		if (!player->played[n]) return 0;
	}

	return 1;
}

void next_player(Truco *truco) {

	if (truco->hand == 0 && is_hand_clear(truco, truco->hand)) {
		truco->current_player = truco->start_player;
		return ;
	}

	/* If nobody played the first hand*/
	if (is_hand_clear(truco, truco->hand)) {
		truco->current_player ++;
		if (truco->current_player >= truco->player_count) truco->current_player = 0;
	} else if (is_hand_full(truco, truco->hand)) {
		/* If all played the hand ... */
		/* TODO: Check who won the hand */

		if (truco->hand == 2) {
			next_round(truco);
			return ;
		}

		/* Ends the hand */
		truco->hand ++;
		truco->current_player ++;
		if (truco->current_player >= truco->player_count) truco->current_player = 0;
	} else {
		/* Hand not finish */
		truco->current_player ++;
		if (truco->current_player >= truco->player_count) truco->current_player = 0;
	}
}

void next_round(Truco *truco) {

	/* Next "start player" */
	truco->start_player ++;
	if (truco->start_player >= truco->player_count) truco->start_player = 0;

	truco->current_player = truco->start_player;

	truco->hand = 0;

	/* Merge deck */
	deck_merge(truco->deck);

	/* Deal cards */
	deal_cards(truco);
}
