#include <ncurses.h>

int main(int argc, char *argv[]) {

    initscr();

    printw("%s", "Truco Argento!!!\n");

    refresh();

    getch();

    endwin();

    return 0;
}
