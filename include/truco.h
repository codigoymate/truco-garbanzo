#ifndef TRUCO_H
#define TRUCO_H

#include <player.h>
#include <card.h>

#define MAIN_MENU_STAGE			0
#define GAME_STAGE				1
#define OPTIONS_STAGE			2

typedef struct {
	int player_count, quit, current_player, start_player;
	int hand;
	int stage, winners[3];
	Player *first_player, *last_player;
	Card *deck[41];

	/* TUI */
	int exit_stage, round_finished;

	/* Logger */
	FILE *log_file;

	/* IA timer */
	long ia_timer;

	/* Options */
	int max_points;
} Truco;

Truco* truco_new(void);
void truco_clean(Truco *truco);

void add_player(Truco *truco, const char *name);
void clean_players(Truco *truco);

Player *get_player(Truco *truco, int index);

void start_game(Truco *truco);

/**
 * @brief Layout players depending terminal dimension
 * 
 * @param truco Truco instance.
 */
void layout_players(Truco *truco);

void increment_current_player(Truco *truco);

/**
 * @brief Determines who is the next player.
 * @param truco Truco instance.
 */
void next_player(Truco *truco);
void next_round(Truco *truco);


#endif
