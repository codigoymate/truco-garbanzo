#include <string_utils.h>
#include <stdlib.h>
#include <string.h>

char *string_set(char *str, const char *l) {
	if (str) str = (char *) realloc(str, strlen(l) + 1);
	else str = (char *) malloc(strlen(l) + 1);

	strcpy(str, l);

	return str;
}

void string_clear(char *str) {
	free(str);
}

char *string_cat(char *str, const char *l) {
	str = (char *) realloc(str, strlen(str) + strlen(l) + 1);
	strcat(str, l);
	return str;
}
