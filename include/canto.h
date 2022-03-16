#ifndef CANTO_H
#define CANTO_H

#include <truco.h>

#define TRUCO           1
#define RETRUCO         2
#define VALE_CUATRO     3

/**
 * @brief Sing truco, retruco or vale-cuatro to increment the points.
 * 
 * @param truco Truco instance.
 * @param player Player who sing.
 */
void canto(Truco *truco, Player *player);

#endif
