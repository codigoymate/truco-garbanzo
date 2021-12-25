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
	int x, y, cursor, count;
	WINDOW *wnd;
	Truco *truco;
} Menu;

Menu *menu_new(Truco *truco, WINDOW *wnd, int x, int y);
void menu_add_item(Menu *menu, const char *name, FUNC_PTR action);
void menu_clean(Menu *menu);
void menu_print(Menu *menu);

void menu_key_event(Menu *menu, int key);

#endif
