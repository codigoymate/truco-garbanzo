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
	menu->cursor = menu->count = 0;
	menu->wnd = wnd;

	return menu;
}

void menu_add_item(Menu *menu, const char *name) {
	MenuItem *item = (MenuItem *) malloc(sizeof(MenuItem));
	item->name = string_set(NULL, name);
	item->next = NULL;

	menu->count ++;

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
	int yy = menu->y, index = 0;
	MenuItem *node = menu->first;

	wattron(menu->wnd, COLOR_PAIR(1));

	for (node = menu->first; node != NULL; node = node->next) {
		if (menu->cursor == index) wattron(menu->wnd, A_REVERSE);
        mvwprintw(menu->wnd, yy, menu->x, "%s", node->name);
		if (menu->cursor == index) wattroff(menu->wnd, A_REVERSE);
		yy ++; index ++;
    }

	wattroff(menu->wnd, COLOR_PAIR(1));
}

void menu_up_event(Menu *menu) {
	menu->cursor --;
	if (menu->cursor < 0) menu->cursor = menu->count - 1;
}

void menu_down_event(Menu *menu) {
	menu->cursor ++;
	if (menu->cursor >= menu->count) menu->cursor = 0;
}

int menu_action(Menu *menu) {
	return menu->cursor;
}