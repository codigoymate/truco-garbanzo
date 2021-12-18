#ifndef TMENU_H
#define TMENU_H

typedef struct Menu {
	char *name;
	struct Menu *next;
} Menu;

Menu *menu_add_item(Menu *menu, const char *name);

#endif
