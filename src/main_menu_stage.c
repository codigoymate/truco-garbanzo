#include <main_menu_stage.h>

#include <tmenu.h>
#include <ncurses.h>

int exit_stage;

void one_oponent(Truco *truco);
void two_oponents(Truco *truco);
void three_oponents(Truco *truco);
void quit(Truco *truco);

void run_main_menu(Truco *truco) {
    Menu *menu;
    WINDOW *menuw;

    menuw = newwin(6, 22, 5, 20);
    menu = menu_new(truco, menuw, 1, 1);

    menu_add_item(menu, "    Un Oponente     ", one_oponent);
    menu_add_item(menu, "   Dos Oponentes    ", two_oponents);
    menu_add_item(menu, "   Tres Oponentes   ", three_oponents);
    menu_add_item(menu, "       Salir        ", quit);

    exit_stage = 0;

    while (!exit_stage) {
        clear();
        wclear(menuw);

        // Title
        attron(COLOR_PAIR(2));
        mvprintw(2, 5, "%s", "<< Truco Argentino >>");
        attroff(COLOR_PAIR(2));


        // Menu
        box(menuw, 0, 0);
        menu_print(menu);

        refresh();
        wrefresh(menuw);

        menu_key_event(menu, getch());
    }

    menu_clean(menu);
    delwin(menuw);
}

void one_oponent(Truco *truco) {
    truco->playerCount = 2;
    start_game(truco);
    truco->stage = GAME_STAGE;
    exit_stage = 1;
}

void two_oponents(Truco *truco) {
    truco->playerCount = 4;
    start_game(truco);
    truco->stage = GAME_STAGE;
    exit_stage = 1;
}

void three_oponents(Truco *truco) {
    truco->playerCount = 6;
    start_game(truco);
    truco->stage = GAME_STAGE;
    exit_stage = 1;
}

void quit(Truco *truco) {
    exit_stage = 1;
    truco->quit = 1;
}
