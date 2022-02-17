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

Menu *menu_new(Truco *truco, int x, int y, int w, int h);
void menu_add_item(Menu *menu, const char *name, FUNC_PTR action);
void menu_clean(Menu *menu);
void menu_print(Menu *menu);

void menu_key_event(Menu *menu, int key);

#endif
