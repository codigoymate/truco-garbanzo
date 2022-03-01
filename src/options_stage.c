#include <options_stage.h>

#include <ncurses.h>
#include <tmenu.h>
#include <string_utils.h>

void max_points(Truco *truco);
void back(Truco *truco);

/* Menu items */
MenuItem *max_points_item;

void run_options(Truco *truco) {

    int key = 0;

    Menu *menu = menu_new(truco, 10, 3, 25, 5);

    max_points_item = menu_add_item(menu, "  Partida a 30 puntos  ", max_points);
    menu_add_item(menu, "         Volver        ", back);

    while (!truco->exit_stage) {
        clear();
        wclear(menu->wnd);

        menu_print(menu);
        refresh();
        wrefresh(menu->wnd);

        key = getch();

        menu_key_event(menu, key);
    }

    menu_clean(menu);
    
}

void max_points(Truco *truco) {
    if (truco->max_points == 30) {
        truco->max_points = 15;
        max_points_item->name = string_set(max_points_item->name, "  Partida a 15 puntos  ");
    } else {
        truco->max_points = 30;
        max_points_item->name = string_set(max_points_item->name, "  Partida a 30 puntos  ");
    }
}

void back(Truco *truco) {
    truco->stage = MAIN_MENU_STAGE;
    truco->exit_stage = 1;
}
