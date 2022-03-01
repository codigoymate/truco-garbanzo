#include <options_stage.h>

#include <ncurses.h>
#include <tmenu.h>

void points(Truco *truco);
void back(Truco *truco);

void run_options(Truco *truco) {

    int key = 0;

    Menu *menu = menu_new(truco, 10, 3, 25, 5);

    menu_add_item(menu, "  Partida a 30 puntos  ", points);
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

void points(Truco *truco) {

}

void back(Truco *truco) {
    truco->stage = MAIN_MENU_STAGE;
    truco->exit_stage = 1;
}
