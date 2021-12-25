#include <tmenu.h>
#include <string_utils.h>
#include <stdlib.h>

void item_clean(MenuItem *item) {
	string_clear(item->name);
	free(item);
}

MenuItem *get_selected_item(Menu *menu) {
	int i = 0;
	MenuItem *item;

	for (item = menu->first; item; item = item->next) {
		if (i == menu->cursor) return item;
		i ++;
	}

	return NULL;
}

Menu *menu_new(Truco *truco, WINDOW *wnd, int x, int y) {
	Menu *menu = (Menu *) malloc(sizeof(Menu));
	menu->first = NULL;
	menu->x = x; menu->y = y;
	menu->cursor = menu->count = 0;
	menu->wnd = wnd;
	menu->truco = truco;

	return menu;
}

void menu_add_item(Menu *menu, const char *name, FUNC_PTR action) {
	MenuItem *item = (MenuItem *) malloc(sizeof(MenuItem));
	item->name = string_set(NULL, name);
	item->action = action;
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

void menu_key_event(Menu *menu, int key) {
	switch (key) {
	case KEY_DOWN:
		menu->cursor ++;
		if (menu->cursor >= menu->count) menu->cursor = 0;
		break;
	case KEY_UP:
		menu->cursor --;
		if (menu->cursor < 0) menu->cursor = menu->count - 1;
		break;
	case 10:
		(*get_selected_item(menu)->action)(menu->truco);
		break;
	
	default:
		break;
	}
}
