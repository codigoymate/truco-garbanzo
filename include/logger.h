#ifndef LOGGER_H
#define LOGGER_H

#define LOGGER_LINES        4
#define LOGGER_MAX          40

typedef struct {
    char line[LOGGER_LINES][LOGGER_MAX];
} Logger;

void log_init(void);
void log_clean(void);

void log_print(char *str);
void log_draw(void);

#endif
