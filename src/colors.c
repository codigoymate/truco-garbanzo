#include <colors.h>

#include <ncurses.h>

void init_colors(void) {

    int bg, fg, p = 1;

    /* Init color pairs */
    for (bg = 0; bg < 8; bg ++) {
        for (fg = 0; fg < 8; fg ++) {
            init_pair(p, fg, bg); p ++;
        }
    }

    /* Title */
    init_pair(PAIR_TITLE, COLOR_CYAN, COLOR_BLACK);

    /* Menu */
    init_pair(PAIR_MENU, COLOR_GREEN, COLOR_BLACK);

	/* Draw card */
    init_pair(PAIR_CARD, COLOR_BLACK, COLOR_WHITE);
    init_pair(PAIR_CARD_ORO, COLOR_YELLOW, COLOR_WHITE);
    init_pair(PAIR_CARD_COPAS, COLOR_GREEN, COLOR_WHITE);
    init_pair(PAIR_CARD_ESPADAS, COLOR_CYAN, COLOR_WHITE);
    init_pair(PAIR_CARD_BASTOS, COLOR_GREEN, COLOR_WHITE);

    /* Players */
    init_pair(PAIR_PLAYER0, COLOR_BLUE, COLOR_BLACK);
    init_pair(PAIR_PLAYER1, COLOR_RED, COLOR_BLACK);
}