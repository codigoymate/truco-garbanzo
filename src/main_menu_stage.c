#include <main_menu_stage.h>

#include <tmenu.h>
#include <ncurses.h>
#include <colors.h>

void one_oponent(Truco *truco);
void two_oponents(Truco *truco);
void three_oponents(Truco *truco);
void options(Truco *truco);
void quit(Truco *truco);

void run_main_menu(Truco *truco) {
    Menu *menu;

    menu = menu_new(truco, 20, 5, 22, 7);

    menu_add_item(menu, "    Un Oponente     ", one_oponent);
    menu_add_item(menu, "   Dos Oponentes    ", two_oponents);
    menu_add_item(menu, "   Tres Oponentes   ", three_oponents);
    menu_add_item(menu, "      Opciones      ", options);
    menu_add_item(menu, "       Salir        ", quit);

    while (!truco->exit_stage) {
        clear();
        wclear(menu->wnd);

        /* Title */
        attron(COLOR_PAIR(PAIR_TITLE));
        mvprintw(2, 5, "%s", "<< Truco Argentino >>");
        attroff(COLOR_PAIR(PAIR_TITLE));

        /* Menu */ 
        menu_print(menu);

        refresh();
        wrefresh(menu->wnd);

        menu_key_event(menu, getch());
    }

    menu_clean(menu);
}

void one_oponent(Truco *truco) {
    truco->player_count = 2;
    start_game(truco);
    truco->stage = GAME_STAGE;
    truco->exit_stage = 1;
}

void two_oponents(Truco *truco) {
    truco->player_count = 4;
    start_game(truco);
    truco->stage = GAME_STAGE;
    truco->exit_stage = 1;
}

void three_oponents(Truco *truco) {
    truco->player_count = 6;
    start_game(truco);
    truco->stage = GAME_STAGE;
    truco->exit_stage = 1;
}

void options(Truco *truco) {
    truco->stage = OPTIONS_STAGE;
    truco->exit_stage = 1;
}

void quit(Truco *truco) {
    truco->exit_stage = 1;
    truco->quit = 1;
}
