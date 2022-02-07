#include <logger.h>
#include <ncurses.h>

void log_init(Truco *truco) {
    truco->logw = newwin(5, 80, 20, 60);
    scrollok(truco->logw, TRUE);
}
void log_clean(Truco *truco) {
    delwin(truco->logw);
}

void log_print(Truco *truco, char *str) {
    wprintw(truco->logw, "%s\n", str);
}
