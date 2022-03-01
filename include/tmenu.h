#ifndef TMENU_H
#define TMENU_H

#include <ncurses.h>
#include <truco.h>

typedef void (*FUNC_PTR)(Truco *);

typedef struct MenuItem {
	char *name;
	struct MenuItem *next;
	void (*action)(Truco *);
} MenuItem;

typedef struct Menu {
	MenuItem *first, *last;
	int x, y, w, h, cursor, count;
	WINDOW *wnd;
	Truco *truco;
} Menu;

/**uno debajo de otro
 * @brief Create a menu with window container.
 * 
 * @param truco Truco instance.
 * @param x X coord of the window.
 * @param y Y coord of the window.
 * @param w width of the window.
 * @param h height coord of the window.
 * @return Menu* instance of the new window.
 */
Menu *menu_new(Truco *truco, int x, int y, int w, int h);

/**
 * @brief Add an item to menu.
 * The item will printed in order, one below another.
 * When the item is selected and press 'Enter', fuction "action" is
 * called. The parameter of the function is the Truco instance.
 * 
 * @param menu Menu instance.
 * @param name Name of the item.
 * @param action Action fuction pointer.
 * @return MenuItem* the menu item instance.
 */
MenuItem *menu_add_item(Menu *menu, const char *name, FUNC_PTR action);

/**
 * @brief Clean the menu from memory, and containing items too.
 * 
 * @param menu Menu instance.
 */
void menu_clean(Menu *menu);

/**
 * @brief Print the menu before refresh window. You must refresh the
 * window with wrefresh(menu->wnd).
 * 
 * @param menu Menu instance.
 */
void menu_print(Menu *menu);

/**
 * @brief Pass the pressed key to menu.
 * Menu react with keys up, down, left and right to select items, and
 * enter to call action function's item.
 * 
 * @param menu Menu instance.
 * @param key Key event.
 */
void menu_key_event(Menu *menu, int key);

#endif
