#include <game_stage.h>

#include <ncurses.h>
#include <string_utils.h>
#include <deck.h>
#include <ia.h>
#include <tmenu.h>
#include <colors.h>
#include <logger.h>
#include <human.h>
#include <timing.h>
#include <points.h>

void draw_game(Truco *truco, WINDOW *wnd);
void draw_statusbar(Truco *truco, WINDOW *wnd);

void next(Truco *truco);
void back(Truco *truco);

void run_game(Truco *truco) {

	int key;
	PointTable *points;
	points = point_table_new(truco, 60, 3, 40, 20);

	log_init();

	log_print("Partida iniciada");

	next_round(truco);

	nodelay(stdscr, TRUE);

    while (!truco->exit_stage) {

		clear();

		/* Draw */
		draw_game(truco, stdscr);
		draw_statusbar(truco, stdscr);

		log_draw();

		refresh();

		delay(100);

		key = getch();

		switch (key) {
		case KEY_RESIZE:
			layout_players(truco);
			break;

		case 27:
			truco->exit_stage = 1;
			truco->stage = MAIN_MENU_STAGE;
			break;
		}

		/* Update */
		if (!truco->round_finished) {
			if (truco->current_player == 0)
				human_play(truco, key);
			else
				ia_play(truco);
		} else {
			/* Show results */
			point_table_draw(points);

			truco->round_finished = 0;
			next_round(truco);
		}

	}

	nodelay(stdscr, FALSE);

	point_table_clean(points);

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
	if (truco->player_count > 2) {
		mvwprintw(wnd, 1, 60, "Ellos: %d", get_player(truco, 1)->score);
		mvwprintw(wnd, 2, 60, "Nosotros: %d", get_player(truco, 0)->score);
	} else {
		mvwprintw(wnd, 1, 60, "%s: %d",
				get_player(truco, 1)->name, get_player(truco, 1)->score);
		mvwprintw(wnd, 2, 60, "%s: %d",
				get_player(truco, 0)->name, get_player(truco, 0)->score);
	}
	
	/* Draw human controls */
	human_draw_controls(truco, w, h);
	
	/* Draw human cards */
	for (i = 0; i < 3; i ++) {
		if (truco->first_player->hand[i]) {
			mvwaddch(wnd, h - 9, w - 33 + 10 * i, '[' | COLOR_PAIR(PAIR_HUMAN_CONTROL));
			wattron(wnd, COLOR_PAIR(PAIR_SHORTCUT));
			wprintw(wnd, "%i", i + 1);
			wattroff(wnd, COLOR_PAIR(PAIR_SHORTCUT));
			waddch(wnd, ']' | COLOR_PAIR(PAIR_HUMAN_CONTROL));
			card_draw(wnd, truco->first_player->hand[i], w - 33 + 10 * i, h - 8);
		}
	}
}

void draw_statusbar(Truco *truco, WINDOW *wnd) {
	int w, h, i;
	getmaxyx(wnd, h, w);

	wattron(wnd, COLOR_PAIR(PAIR_STATUSBAR));
	for (i = 0; i < w; i ++) {
		mvwaddch(wnd, h - 1, i, ' ');
	}

	mvwprintw(wnd, h - 1, 0, " Turno de %s", get_player(truco, truco->current_player)->name);

	wattroff(wnd, COLOR_PAIR(PAIR_STATUSBAR));
}