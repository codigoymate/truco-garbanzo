#include <tmenu.h>
#include <string_utils.h>
#include <stdlib.h>

void item_clean(MenuItem *item) {
	string_clear(item->name);
	free(item);
}

Menu *menu_new(WINDOW *wnd, int x, int y) {
	Menu *menu = (Menu *) malloc(sizeof(Menu));
	menu->first = NULL;
	menu->x = x; menu->y = y;
	menu->wnd = wnd;

	return menu;
}

void menu_add_item(Menu *menu, const char *name) {
	MenuItem *item = (MenuItem *) malloc(sizeof(MenuItem));
	item->name = string_set(NULL, name);
	item->next = NULL;

	if (!menu->first) {
		menu->first = item;
		menu->last = item;
		return ;
	}

	menu->last->next = item;
	menu->last = item;
}

void menu_clean(Menu *menu) {
	MenuItem *item = menu->first, *next;

	if (item) {

		while (item) {
			next = item->next;
			item_clean(item);
			item = next;
		}

	}

	free(menu);
}

void menu_print(Menu *menu) {
	int yy = menu->y;
	MenuItem *node = menu->first;

	wattron(menu->wnd, COLOR_PAIR(1));

	for (node = menu->first; node != NULL; node = node->next) {
		
        mvwprintw(menu->wnd, yy, menu->x, "%s", node->name);
		yy ++;
    }

	wattroff(menu->wnd, COLOR_PAIR(1));
}

