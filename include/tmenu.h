#ifndef TMENU_H
#define TMENU_H

#include <ncurses.h>

typedef struct MenuItem {
	char *name;
	struct MenuItem *next;
} MenuItem;

typedef struct Menu {
	MenuItem *first, *last;
	int x, y, cursor, count;
	WINDOW *wnd;
} Menu;

Menu *menu_new(WINDOW *wnd, int x, int y);
void menu_add_item(Menu *menu, const char *name);
void menu_clean(Menu *menu);
void menu_print(Menu *menu);

void menu_up_event(Menu *menu);
void menu_down_event(Menu *menu);

int menu_action(Menu *menu);

#endif
