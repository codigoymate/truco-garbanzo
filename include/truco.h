#ifndef TRUCO_H
#define TRUCO_H

#include <player.h>
#include <card.h>

//#define MAX_PLAYERS			6

#define MAIN_MENU_STAGE			0
#define GAME_STAGE				1

typedef struct {
	int playerCount, quit, current_player;
	int stage;
	Player *first_player, *last_player;
	Card *deck[40];
} Truco;

Truco* truco_new(void);
void truco_clean(Truco *truco);

void add_player(Truco *truco, const char *name);
void clean_players(Truco *truco);

Player *get_player(Truco *truco, int index);

void start_game(Truco *truco);


#endif
