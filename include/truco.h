#ifndef TRUCO_H
#define TRUCO_H

#include <player.h>

//#define MAX_PLAYERS			6

#define MAIN_MENU_STAGE			0
#define GAME_STAGE				1

typedef struct {
	int playerCount, quit;
	int stage;
	Player *first_player, *last_player;
} Truco;

Truco* truco_new(void);
void truco_clean(Truco *truco);

void add_player(Truco *truco, const char *name);
void clean_players(Truco *truco);

void start_game(Truco *truco);


#endif
