#include <tmenu.h>
#include <string_utils.h>
#include <stdlib.h>

void item_clean(Menu *menu) {
	string_clear(menu->name);
	free(menu);
}

Menu *menu_add_item(Menu *menu, const char *name) {
	Menu *n;
	Menu *node = (Menu *) malloc(sizeof(Menu));
	node->name = string_set(NULL, name);
	node->next = NULL;
	
	if (!menu) return node;

	n = menu;

	while (n->next != NULL) n = n->next;

	n->next = node;

	return menu;
}

void menu_clean(Menu *menu) {
	Menu *node = menu, *next;

	if (!node) return ;

	while (node) {
		next = node->next;
		item_clean(node);
		node = next;
	}
}
