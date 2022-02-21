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
/*void draw_score(Truco *truco, WINDOW *wnd);*/
void draw_round_results(Truco *truco, WINDOW *wnd);

void next(Truco *truco);
void back(Truco *truco);

void run_game(Truco *truco) {

	int key;

	/*Menu *menu;*/
	WINDOW *resultsw;

/*	menu = menu_new(truco, 60, 3, 12, 4);*/

	/*scorew = newwin(3, 15, 2, 80);*/
	resultsw = newwin(3, 15, 10, 80);

	log_init(truco);

	/*menu_add_item(menu, "   Next   ", next);
	menu_add_item(menu, "   Back   ", back);*/

	log_print(truco, "Partida iniciada");

	next_round(truco);

	nodelay(stdscr, TRUE);

    while (!truco->exit_stage) {

		clear();
		/*wclear(scorew);*/
		if (truco->round_finished) wclear(resultsw);

		/* Draw */
		draw_game(truco, stdscr);
		/*draw_score(truco, scorew);*/
		if (truco->round_finished) draw_round_results(truco, resultsw);

		refresh();
		if (truco->round_finished) wrefresh(resultsw);
		wrefresh(truco->logw);
		/*wrefresh(scorew);*/

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

	log_clean(truco);
	/*delwin(scorew);*/
	delwin(resultsw);
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
			card_draw(wnd, truco->first_player->hand[i], w - 33 + 10 * i, h - 8);
		}
	}
}

/*void next(Truco *truco) {
	ia_play(truco);
	next_player(truco);
}

void back(Truco *truco) {
	truco->stage = MAIN_MENU_STAGE;
	truco->exit_stage = 1;
}*/

/*void draw_score(Truco *truco, WINDOW *wnd) {
	
}*/

void draw_round_results(Truco *truco, WINDOW *wnd) {
	wprintw(wnd, "Round finished.");
}
