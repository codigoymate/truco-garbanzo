#ifndef TRUCO_H
#define TRUCO_H

typedef struct {
	int playerCount;
} Truco;

extern Truco *truco;

void truco_init(void);
void truco_clean(void);


#endif
