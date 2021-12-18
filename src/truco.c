#include <truco.h>
#include <malloc.h>

Truco *truco;

void truco_init(void) {
	truco = (Truco *) malloc(sizeof(truco));
}

void truco_clean(void) {
	free(truco);
}
