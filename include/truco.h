#ifndef TRUCO_H
#define TRUCO_H

#include <player.h>

#define MAX_PLAYERS			6

#define MAIN_MENU_STAGE			0
#define GAME_STAGE				1

typedef struct {
	int playerCount, quit;
	int stage;
	Player *players[MAX_PLAYERS];
} Truco;

Truco* truco_new(void);
void truco_clean(Truco *truco);

void start_game(Truco *truco);


#endif
