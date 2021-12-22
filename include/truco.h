#ifndef TRUCO_H
#define TRUCO_H

#define MAIN_MENU_STAGE			0
#define GAME_STAGE				1

typedef struct {
	int playerCount, quit;
	int stage;
} Truco;

extern Truco *truco;

void truco_init(void);
void truco_clean(void);


#endif
