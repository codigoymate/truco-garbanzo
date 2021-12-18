#include <ncurses.h>
#include <truco.h>

#include <tmenu.h>

int main(int argc, char *argv[]) {

    Menu *menu = NULL;

    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    truco_init();

    menu = menu_new(stdscr, 20, 5);

    menu_add_item(menu, "    Item 1    ");
    menu_add_item(menu, "    Item 2    ");
    menu_add_item(menu, "    Item 3    ");

    menu_print(menu);

    refresh();
    getch();

    menu_clean(menu);

    truco_clean();
    endwin();

    return 0;
}
