#include <human.h>

#include <player.h>
#include <time.h>
#include <colors.h>
#include <ctype.h>

void human_play(Truco *truco, int key) {

    if (truco->first_player->surrendered) {
		next_player(truco);
		return ;
	}

    key = toupper(key);

    switch (key) {
    case '1':
    case '2':
    case '3':
        if (play_card(truco->first_player, key - '1')) {
            truco->ia_timer = clock() + (CLOCKS_PER_SEC / 1000) * 1000;
            next_player(truco);
        }
        break;

    case 'M':
        /* Give up */
        give_up(truco->first_player, truco->deck);
        truco->ia_timer = clock() + (CLOCKS_PER_SEC / 1000) * 1000;
        next_player(truco);
        break;

    default:
        break;
    }

}

void human_draw_controls(Truco *truco, int w, int h) {
    /* Give up */
    mvaddch(h - 11, w - 33, 'M' | COLOR_PAIR(PAIR_SHORTCUT));
    attron(COLOR_PAIR(PAIR_HUMAN_CONTROL));
    printw("e voy al mazo");
    attroff(COLOR_PAIR(PAIR_HUMAN_CONTROL));
}
