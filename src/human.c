#include <human.h>

#include <player.h>
#include <canto.h>
#include <time.h>
#include <colors.h>
#include <ctype.h>

void draw_option(int x, int y, const char *key, const char *name);

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

    case 'T':
        /* Truco, retruco and vale-cuatro */
        if (canto(truco, truco->first_player)) {
            truco->canto_mode = 1;
            /* Player turn back */
            truco->current_player --;
            if (truco->current_player < 0) truco->current_player = truco->player_count - 1;
            truco->ia_timer = clock() + (CLOCKS_PER_SEC / 1000) * 1000;
        }

        break;

    default:
        break;
    }

}

void draw_option(int x, int y, const char *key, const char *name) {
    attron(COLOR_PAIR(PAIR_SHORTCUT));
    mvprintw(y, x, key);
    attroff(COLOR_PAIR(PAIR_SHORTCUT));

    attron(COLOR_PAIR(PAIR_HUMAN_CONTROL));
    mvprintw(y, x + 6, name);
    attroff(COLOR_PAIR(PAIR_HUMAN_CONTROL));
}

void human_draw_controls(Truco *truco, int w, int h) {

    int y = h - 11;

    draw_option(w - 33, y, "[Esc]", "Salir."); y --;

    if (truco->current_player == 0) {

        /* Give up */

        draw_option(w - 33, y, "[M]", "Me voy al mazo."); y --;

        if (truco->canto_team != 0) {
            switch (truco->current_canto) {
            case 0:
                draw_option(w - 33, y, "[T]", "Truco."); y --;
                break;
            }
        }
    }
}
