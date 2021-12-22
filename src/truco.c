#include <truco.h>
#include <malloc.h>

Truco *truco;

void truco_init(void) {
	truco = (Truco *) malloc(sizeof(truco));
	truco->quit = 0;
	truco->stage = MAIN_MENU_STAGE;
}

void truco_clean(void) {
	free(truco);
}
