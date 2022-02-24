#include <game_stage.h>

#include <ncurses.h>
#include <string_utils.h>
#include <deck.h>
#include <ia.h>
#include <tmenu.h>
#include <colors.h>
#include <logger.h>
#include <human.h>

void draw_game(Truco *truco, WINDOW *wnd);

void next(Truco *truco);
void back(Truco *truco);

void run_game(Truco *truco) {

	int key;

	log_init();

	log_print("Partida iniciada");

	next_round(truco);

	nodelay(stdscr, TRUE);

    while (!truco->exit_stage) {

		clear();

		/* Draw */
		draw_game(truco, stdscr);

		refresh();
		/* wrefresh(truco->logw); */

		key = getch();

		if (key == KEY_RESIZE) {
			layout_players(truco);
		}

		/* Update */
		if (!truco->round_finished) {
			if (truco->current_player == 0)
				human_play(truco, key);
			else {
				ia_play(truco);
				next_player(truco);
			}
		} else {
			truco->round_finished = 0;
			next_round(truco);
		}

		/* Human player event */
		if (truco->current_player == 0) {
			human_play(truco, key);
		}
	}

	nodelay(stdscr, FALSE);

	log_clean();
}

void draw_game(Truco *truco, WINDOW *wnd) {
	Player *player;
	int i = 0, c, w, h;

	getmaxyx(stdscr, h, w);

	for (player = truco->first_player; player != NULL; player = player->next) {
		if (truco->current_player == i) 
			wattron(wnd, A_REVERSE);

		if (player->id % 2) wattron(wnd, COLOR_PAIR(PAIR_PLAYER1));
		else wattron(wnd, COLOR_PAIR(PAIR_PLAYER0));

		/* Draw players */
		mvwprintw(wnd, player->ty, player->tx, "%s", player->name);

		/* Markup the start player */
		if (i == truco->start_player)
			wprintw(wnd, "%s", " (*)");

		if (player->id % 2) wattroff(wnd, COLOR_PAIR(PAIR_PLAYER1));
		else wattroff(wnd, COLOR_PAIR(PAIR_PLAYER0));

		if (truco->current_player == i)
			wattroff(wnd, A_REVERSE);

		/* Draw cards */
		for (c = 0; c < 3; c ++) {
			if (!player->played[c]) continue;
			card_draw_small(wnd, player->played[c], player->tx + c * 4, player->ty + 1);
		}

		i ++;
	}

	/* Score */
	mvwprintw(wnd, 1, 60, "Nosotros: %d", get_player(truco, 0)->score);
	mvwprintw(wnd, 2, 60, "Ellos: %d", get_player(truco, 1)->score);
	
	/* Draw player 0 card */
	for (i = 0; i < 3; i ++) {
		if (truco->first_player->hand[i]) {
			mvwprintw(wnd, h - 9, w - 33 + 10 * i, "[%i]", i + 1);
			card_draw(wnd, truco->first_player->hand[i], w - 33 + 10 * i, h - 8);
		}
	}
}
