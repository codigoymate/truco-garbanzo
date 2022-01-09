#include <colors.h>

#include <ncurses.h>

void init_colors(void) {

    /* Title */
    init_pair(PAIR_TITLE, COLOR_CYAN, COLOR_BLACK);

    /* Menu */
    init_pair(PAIR_MENU, COLOR_GREEN, COLOR_BLACK);

	/* Draw card */
    init_pair(PAIR_CARD, COLOR_BLACK, COLOR_WHITE);
    init_pair(PAIR_CARD_ORO, COLOR_YELLOW, COLOR_WHITE);
    init_pair(PAIR_CARD_COPAS, COLOR_BLUE, COLOR_WHITE);
    init_pair(PAIR_CARD_ESPADAS, COLOR_CYAN, COLOR_WHITE);
    init_pair(PAIR_CARD_BASTOS, COLOR_GREEN, COLOR_WHITE);
}