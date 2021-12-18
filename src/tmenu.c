#include <tmenu.h>
#include <string_utils.h>
#include <stdlib.h>

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
