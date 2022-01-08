#include <game_stage.h>

#include <ncurses.h>
#include <string_utils.h>
#include <deck.h>
#include <ia.h>

void draw_game(Truco *truco);

void run_game(Truco *truco) {

	next_round(truco);

    while (1) {
		clear();

		/*if (truco->current_player != 0) {*/
			ia_play(truco);
			next_player(truco);
		/*}*/

		draw_game(truco);

		refresh();

		getch();
	}
}

void draw_game(Truco *truco) {
	Player *player;
	char *name;
	int i = 0, c;

	for (player = truco->first_player; player != NULL; player = player->next) {
		if (truco->current_player == i) 
			attron(A_REVERSE);
		mvprintw(player->ty, player->tx, "%s", player->name);

		for (c = 0; c < 3; c ++) {
			if (!player->played[c]) continue;
			name = card_short_name(player->played[c]);
			mvprintw(player->ty + 1, player->tx + c * 4, "%s", name);
			string_clear(name);
		}

		if (truco->current_player == i)
			attroff(A_REVERSE);
		i ++;
	}
}

