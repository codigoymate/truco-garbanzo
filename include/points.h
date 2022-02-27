#ifndef POINTS_H
#define POINTS_H

#include <truco.h>

/**
 * @brief Uses to show the point table window on finalize round.
 */
typedef struct {
    Truco *truco;
    WINDOW *wnd;
} PointTable;

PointTable *point_table_new(Truco *truco, int x, int y, int w, int h);
void point_table_clean(PointTable *pt);
void point_table_draw(PointTable *pt);

/**
 * @brief Sum "points" to actual "team". Point values
 * are stored in all player struct.
 * 
 * @param truco truco instance.
 * @param points points to give.
 * @param team team wich receive points.
 */
void give_points(Truco *truco, int points, int team);

#endif
