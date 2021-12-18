#include <ncurses.h>
#include <truco.h>

int main(int argc, char *argv[]) {

    initscr();

    truco_init();

    printw("%s", "Truco Argento!!!\n");

    refresh();

    getch();

    truco_clean();

    endwin();

    return 0;
}
