#include <game_stage.h>

#include <ncurses.h>
#include <string_utils.h>
#include <deck.h>
#include <ia.h>
#include <tmenu.h>

void draw_game(Truco *truco, WINDOW *wnd);

void next(Truco *truco);
void back(Truco *truco);

void run_game(Truco *truco) {

	int key;

	Menu *menu;
	WINDOW *menuw, *gamew;

	menuw = newwin(4, 20, 3, 60);
	menu = menu_new(truco, menuw, 1, 1);

	gamew = newwin(25, 55, 1, 2);

	menu_add_item(menu, "   Next   ", next);
	menu_add_item(menu, "   Back   ", back);

	next_round(truco);

    while (!truco->exit_stage) {
		clear();

		draw_game(truco, gamew);

		box(menuw, 0, 0);
		menu_print(menu);

		refresh();
		wrefresh(gamew);
		wrefresh(menuw);

		key = getch();

		menu_key_event(menu, key);
	}

	delwin(gamew);
	delwin(menuw);
	menu_clean(menu);
}

void draw_game(Truco *truco, WINDOW *wnd) {
	Player *player;
	char *name;
	int i = 0, c;

	for (player = truco->first_player; player != NULL; player = player->next) {
		if (truco->current_player == i) 
			wattron(wnd, A_REVERSE);
		mvwprintw(wnd, player->ty, player->tx, "%s", player->name);

		/* Markup the start player */
		if (i == truco->start_player)
			wprintw(wnd, "%s", " (*)");

		for (c = 0; c < 3; c ++) {
			if (!player->played[c]) continue;
			name = card_short_name(player->played[c]);
			mvwprintw(wnd, player->ty + 1, player->tx + c * 4, "%s", name);
			string_clear(name);
		}

		if (truco->current_player == i)
			wattroff(wnd, A_REVERSE);
		i ++;
	}
}

void next(Truco *truco) {
	ia_play(truco);
	next_player(truco);
}

void back(Truco *truco) {
	truco->stage = MAIN_MENU_STAGE;
	truco->exit_stage = 1;
}