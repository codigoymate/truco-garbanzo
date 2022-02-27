#include <points.h>

#include <logger.h>
#include <string_utils.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

void draw_table(Truco *truco, WINDOW *wnd);
void draw_point_squares(WINDOW *wnd, int x, int y, int points);

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

    draw_table(pt->truco, pt->wnd);

    draw_point_squares(pt->wnd, pt->wnd->_maxx / 4 - 2, 4, pt->truco->first_player->score);
    draw_point_squares(pt->wnd, pt->wnd->_maxx / 4 * 3 - 2, 4, pt->truco->first_player->next->score);

    mvwprintw(pt->wnd, pt->wnd->_maxy - 1, 3, "<Enter> para continuar.");

    wrefresh(pt->wnd);

    /* Waits for Enter key */
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

void draw_table(Truco *truco, WINDOW *wnd) {
    mvwvline(wnd, 1, wnd->_maxx / 2, 0, wnd->_maxy - 2);
    mvwhline(wnd, 3, 2, 0, wnd->_maxx - 3);
    mvwaddch(wnd, 3, wnd->_maxx / 2, ACS_PLUS | A_ALTCHARSET);

    /* Team names */
    if (truco->player_count > 2) {
        mvwprintw(wnd, 2, wnd->_maxx / 4 - 4, "Nosotros");
        mvwprintw(wnd, 2, wnd->_maxx / 4 * 3 - 2, "Ellos");
    } else {
        mvwprintw(wnd, 2, wnd->_maxx / 4 - strlen(truco->first_player->name) / 2, truco->first_player->name);
        mvwprintw(wnd, 2, wnd->_maxx / 4 * 3 - strlen(truco->first_player->next->name) / 2, truco->first_player->next->name);
    }
}

void draw_point_squares(WINDOW *wnd, int x, int y, int points) {

    if (!points) return ;

    if (points >= 1) {
        mvwaddch(wnd, y + 1, x, ACS_VLINE | A_ALTCHARSET);
    }

    if (points >= 2) {
        mvwaddch(wnd, y, x, ACS_ULCORNER | A_ALTCHARSET);
        mvwaddch(wnd, y, x + 1, ACS_HLINE | A_ALTCHARSET);
        mvwaddch(wnd, y, x + 2, ACS_HLINE | A_ALTCHARSET);
    }

    if (points >= 3) {
        mvwaddch(wnd, y, x + 3, ACS_URCORNER | A_ALTCHARSET);
        mvwaddch(wnd, y + 1, x + 3, ACS_VLINE | A_ALTCHARSET);
    }

    if (points >= 4) {
        mvwaddch(wnd, y + 2, x, ACS_LLCORNER | A_ALTCHARSET);
        mvwaddch(wnd, y + 2, x + 1, ACS_HLINE | A_ALTCHARSET);
        mvwaddch(wnd, y + 2, x + 2, ACS_HLINE | A_ALTCHARSET);
        mvwaddch(wnd, y + 2, x + 3, ACS_LRCORNER | A_ALTCHARSET);
    }

    if (points >= 5) {
        mvwaddch(wnd, y + 1, x + 1, ACS_HLINE | A_ALTCHARSET);
        mvwaddch(wnd, y + 1, x + 2, ACS_HLINE | A_ALTCHARSET);
    }

    if (points > 5) {
        draw_point_squares(wnd, x, y + 3, points - 5);
    }
}
