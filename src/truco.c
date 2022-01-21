#include <truco.h>
#include <malloc.h>
#include <stdlib.h>
#include <string_utils.h>
#include <deck.h>
#include <points.h>

int get_hand_winner(Truco *truco);

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
	truco->round_finished = 0;
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
		get_player(truco, 0)->tx = 20;
		get_player(truco, 0)->ty = 20;
		get_player(truco, 1)->tx = 20;
		get_player(truco, 1)->ty = 0;
		break;
	case 4:
		get_player(truco, 0)->tx = 20;
		get_player(truco, 0)->ty = 20;
		get_player(truco, 1)->tx = 0;
		get_player(truco, 1)->ty = 10;
		get_player(truco, 2)->tx = 20;
		get_player(truco, 2)->ty = 0;
		get_player(truco, 3)->tx = 40;
		get_player(truco, 3)->ty = 10;
		break;

	case 6:
		get_player(truco, 0)->tx = 20;
		get_player(truco, 0)->ty = 20;

		get_player(truco, 1)->tx = 0;
		get_player(truco, 1)->ty = 15;

		get_player(truco, 2)->tx = 0;
		get_player(truco, 2)->ty = 5;

		get_player(truco, 3)->tx = 20;
		get_player(truco, 3)->ty = 0;

		get_player(truco, 4)->tx = 40;
		get_player(truco, 4)->ty = 5;

		get_player(truco, 5)->tx = 40;
		get_player(truco, 5)->ty = 15;

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
	int winner;

	if (truco->hand == 0 && is_hand_clear(truco, truco->hand)) {
		truco->current_player = truco->start_player;
		return ;
	}

	/* If nobody played the first hand*/
	if (is_hand_clear(truco, truco->hand)) {
		increment_current_player(truco);
	/* If all played the hand ... */
	} else if (is_hand_full(truco, truco->hand)) {
		winner = get_hand_winner(truco);

		switch (truco->hand) {
		case 0:
			if (winner != -1) {
				truco->winners[0] = winner % 2;
				truco->current_player = winner;
			} else {
				truco->winners[0] = 2; /* Tie */
				increment_current_player(truco);
			}
			break;
		case 1:
			/* Tie and any team won the hand 0 ... */
			if (winner == -1 && truco->winners[0] != 2) {
				/* Give "1" point to winner team */
				give_points(truco, 1, truco->winners[0]);
				/*next_round(truco);*/
				truco->round_finished = 1;
				return ;
			/* Tie and Tie hand 0 ...*/
			} else if (winner == -1 && truco->winners[0] == 2) {
				truco->winners[1] = 2; /* Tie */
				increment_current_player(truco);
			/* Any team wins the hand 0 and any the hand 1 ...*/
			} else {
				/* Any team wins both hads (0 and 1) ... */
				if (winner % 2 == truco->winners[0]) {
					/* Team which won hand 0 and 1 */
					give_points(truco, 1, truco->winners[0]);
					/*next_round(truco);*/
					truco->round_finished = 1;
					return;
				/* Team 1 wins hand 0 and team 2 wins hand 1 */
				} else {
					truco->winners[1] = winner % 2; 
					truco->current_player = winner;
				}
			}
			break;
		case 2:
			/* Tie */
			if (winner == -1) {
				if (truco->winners[0] != 2) {
					/* Wins who won first hand */
					give_points(truco, 1, truco->winners[0]);
				/* Tie all hands */
				} else {
					/* Wins "start_player" */
					give_points(truco, 1, truco->start_player % 2);
				}
			/* Player winner third hand */
			} else {
				/* Team winner third hand */
				give_points(truco, 1, winner % 2);
			}

			/*next_round(truco);*/
			truco->round_finished = 1;
			return ;
		}

		/* Ends the hand */
		truco->hand ++;
		
	} else {
		/* Hand not finish */
		increment_current_player(truco);
	}
}

void next_round(Truco *truco) {
	int i;

	/* Next "start player" */
	truco->start_player ++;
	if (truco->start_player >= truco->player_count) truco->start_player = 0;

	truco->current_player = truco->start_player;

	truco->hand = 0;
	
	for (i = 0; i < 3; i ++) {
		truco->winners[i] = -1;
		/*
			-1: Not played
			0 : Team 1
			1 : Team 2
			2 : Tie
		*/
	}

	/* Merge deck */
	deck_merge(truco->deck);

	/* Deal cards */
	deal_cards(truco);
}

void increment_current_player(Truco *truco) {
	truco->current_player ++;
	if (truco->current_player >= truco->player_count) truco->current_player = 0;
}

int get_hand_winner(Truco *truco) {
	Player *list[8], *player;
	int i = 0;

	/* Load player list */
	for (player = truco->first_player; player; player = player->next) {
		list[i] = player; i ++;
	}

	/* Sort players by card power */
	for (i = 0; i < truco->player_count - 1; i ++) {
		if (list[i]->played[truco->hand]->power < list[i + 1]->played[truco->hand]->power) {
			player = list[i];
			list[i] = list[i + 1];
			list[i + 1] = player;
			i = -1;
		}
	}

	/* Parda */
	if (list[0]->played[truco->hand]->power == list[1]->played[truco->hand]->power)
		return -1;

	return list[0]->id;
}