#include <ncurses.h>
#include <truco.h>
#include <main_menu_stage.h>
#include <game_stage.h>

#include <stdlib.h>
#include <time.h>

void item1(void);
void item2(void);
void quit(void);

int main(int argc, char *argv[]) {

    Truco *truco;

    srand(time(NULL));

    initscr();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);

    // Draw card ORO
    init_pair(4, COLOR_YELLOW, COLOR_WHITE);

    // Draw card COPAS
    init_pair(5, COLOR_BLUE, COLOR_WHITE);

    // Draw card ESPADAS
    init_pair(6, COLOR_CYAN, COLOR_WHITE);

    // Draw card BASTOD
    init_pair(7, COLOR_GREEN, COLOR_WHITE);

    
    truco = truco_new();

    while (!truco->quit) {
        switch (truco->stage) {
        case MAIN_MENU_STAGE:
            run_main_menu(truco);
            break;
        case GAME_STAGE:
            run_game(truco);
            break;
        }
    }

    truco_clean(truco);
    endwin();

    return 0;
}
