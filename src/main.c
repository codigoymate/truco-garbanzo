#include <ncurses.h>
#include <truco.h>
#include <main_menu_stage.h>
#include <game_stage.h>

void item1(void);
void item2(void);
void quit(void);

int main(int argc, char *argv[]) {

    initscr();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    truco_init();

    while (!truco->quit) {
        switch (truco->stage) {
        case MAIN_MENU_STAGE:
            run_main_menu();
            break;
        case GAME_STAGE:
            run_game();
            break;
        }
    }

    truco_clean();
    endwin();

    return 0;
}
