#include <ncurses.h>
#include <truco.h>
#include <main_menu_stage.h>
#include <game_stage.h>
#include <options_stage.h>
#include <colors.h>

#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char *argv[]) {

    Truco *truco;

    setlocale(LC_ALL, "");
    srand(time(NULL));

    initscr();
    noecho();
    curs_set(0);
    
    start_color();
    init_colors();

    keypad(stdscr, TRUE);

    set_escdelay(0);

    truco = truco_new();

    while (!truco->quit) {

        truco->exit_stage = 0;

        switch (truco->stage) {
        case MAIN_MENU_STAGE:
            run_main_menu(truco);
            break;
        case GAME_STAGE:
            run_game(truco);
            break;
        case OPTIONS_STAGE:
            run_options(truco);
            break;
        }
    }

    truco_clean(truco);
    endwin();

    return 0;
}
