#include <main_menu_stage.h>

#include <truco.h>
#include <tmenu.h>
#include <ncurses.h>

int exit_stage;

void one_oponent(void);
void two_oponents(void);
void three_oponents(void);
void quit(void);

void run_main_menu(void) {
    Menu *menu;
    WINDOW *menuw;

    menuw = newwin(6, 22, 5, 20);
    menu = menu_new(menuw, 1, 1);

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

void one_oponent(void) {

}

void two_oponents(void) {

}

void three_oponents(void) {

}

void quit(void) {
    exit_stage = 1;
    truco->quit = 1;
}
