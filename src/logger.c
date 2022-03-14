#include <logger.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

FILE *log_file;
Logger *logger;

void log_init(void) {
    int i;
    log_file = fopen("truco.log", "a");
    fprintf(log_file, "\n");
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
    char *str_time;
    time_t current_time;

    current_time = time(NULL);
    str_time = ctime(&current_time);
    str_time[strlen(str_time) - 1] = '\0';

    fprintf(log_file, "%s: %s\n", str_time, str);

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