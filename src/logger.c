#include <logger.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

FILE *log_file;
Logger *logger;

void log_init(void) {
    int i;
    log_file = fopen("truco.log", "w");
    logger = (Logger *) malloc(sizeof(Logger));
    for (i = 0; i < LOGGER_LINES; i ++)
        strcpy(logger->line[i], "");
}
void log_clean(void) {
    fclose(log_file);
    free(logger);
}

void log_print(char *str) {
    int i;
    fprintf(log_file, "%s\n", str);

    for (i = 0; i < LOGGER_LINES - 1; i ++) {
        strcpy(logger->line[i], logger->line[i + 1]);
    }

    strcpy(logger->line[LOGGER_LINES - 1], str);
}

void log_draw(void) {
    int i;
    for (i = 0; i < LOGGER_LINES; i ++) {
        mvprintw(i + 4, 60, logger->line[i]);
    }
}