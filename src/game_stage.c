#include <game_stage.h>

#include <ncurses.h>
#include <string_utils.h>
#include <deck.h>
#include <ia.h>
#include <tmenu.h>

void draw_game(Truco *truco, WINDOW *wnd);

void next(Truco *truco);

void run_game(Truco *truco) {

	int key;

	Menu *menu;
	WINDOW *menuw, *gamew;

	menuw = newwin(4, 20, 3, 60);
	menu = menu_new(truco, menuw, 1, 1);

	gamew = newwin(25, 55, 1, 2);

	menu_add_item(menu, "   Next   ", next);

	next_round(truco);

    while (1) {
		clear();

		draw_game(truco, gamew);

		box(menuw, 0, 0);
		menu_print(menu);

		/*box(gamew, 0, 0);*/

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
