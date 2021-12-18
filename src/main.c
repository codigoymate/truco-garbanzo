#include <ncurses.h>
#include <truco.h>

#include <tmenu.h>

int main(int argc, char *argv[]) {

    Menu *menu = NULL, *node = NULL;

    menu = menu_add_item(menu, "Item 1");
    menu = menu_add_item(menu, "Item 2");
    menu = menu_add_item(menu, "Item 3");

    initscr();
    truco_init();

    for (node = menu; node != NULL; node = node->next) {
        printw("%s\n", node->name);
    }

    refresh();
    getch();

    menu_clean(menu);

    truco_clean();
    endwin();

    return 0;
}
