#ifndef HUMAN_H
#define HUMAN_H

#include <truco.h>

void human_play(Truco *truco, int key);

/**
 * @brief Print the human controls in the game stage.
 * 
 * @param truco Truco instance.
 * @param w Max width of the screen.
 * @param h Max height of the screen.
 */
void human_draw_controls(Truco *truco, int w, int h);

#endif