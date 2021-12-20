#include <ncurses.h>
#include <stdlib.h>
#include <truco.h>
#include <tmenu.h>

int q;

void item1(void);
void item2(void);
void quit(void);

int main(int argc, char *argv[]) {
    int key;
    Menu *menu = NULL;

    q = 0;

    initscr();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    truco_init();

    menu = menu_new(stdscr, 20, 5);

    menu_add_item(menu, "    Item 1    ", item1);
    menu_add_item(menu, "    Item 2    ", item2);
    menu_add_item(menu, "     Exit     ", quit);

    while (!q) {
        clear();
        menu_print(menu);
        refresh();

        key = getch();
        menu_key_event(menu, key);

    }

    menu_clean(menu);

    truco_clean();
    endwin();

    return 0;
}

void item1(void) {
    
}

void item2(void) {

}

void quit(void) {
    q = 1;
}
