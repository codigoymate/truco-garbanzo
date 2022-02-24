#include <logger.h>

#include <stdio.h>

FILE *log_file;

void log_init(void) {
    log_file = fopen("truco.log", "w");
}
void log_clean(void) {
    fclose(log_file);
}

void log_print(char *str) {
    fprintf(log_file, "%s\n", str);
}
