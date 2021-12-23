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

extern Truco *truco;

void truco_init(void);
void truco_clean(void);

void start_game(void);


#endif
