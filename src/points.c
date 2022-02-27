#include <points.h>

#include <logger.h>
#include <string_utils.h>
#include <stdlib.h>
#include <ncurses.h>

PointTable *point_table_new(Truco *truco, int x, int y, int w, int h) {
    PointTable *pt = (PointTable *) malloc(sizeof(PointTable));
    pt->truco = truco;
    pt->wnd = newwin(h, w, y, x);

    return pt;
}

void point_table_clean(PointTable *pt) {
    delwin(pt->wnd);
    free(pt);
}

void point_table_draw(PointTable *pt) {

    int key = 0;

    wclear(pt->wnd);
    box(pt->wnd, 0, 0);

    mvwprintw(pt->wnd, pt->wnd->_maxy - 1, 3, "<Enter> para continuar.");

    wrefresh(pt->wnd);

    while (key != 10) key = wgetch(pt->wnd);
}

void give_points(Truco *truco, int points, int team) {
    int i = 0;
    Player *player;
    char *msg = NULL;

    for (player = truco->first_player; player; player = player->next) {
        if (i % 2 == team) player->score += points;
        i ++;
    }

    /* Log */
    msg = string_set(msg, "Equipo ");
    msg = string_cat_number(msg, team + 1);
    msg = string_cat(msg, " obtiene ");
    msg = string_cat_number(msg, points);
    if (points > 1) msg = string_cat(msg, "puntos.");
    else msg = string_cat(msg, " punto.");
    log_print(msg);
    string_clean(msg);
}
