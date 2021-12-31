#include <game_stage.h>

#include <ncurses.h>
#include <string_utils.h>
#include <deck.h>

void run_game(Truco *truco) {

	Player *player;

	deck_merge(truco->deck);
	deal_cards(truco);

    while (1) {
		int i = 0, c;
		clear();

		for (player = truco->first_player; player != NULL; player = player->next) {
			if (truco->current_player == i) 
				attron(A_REVERSE);
			mvprintw(player->ty, player->tx, "%s", player->name);

			for (c = 0; c < 3; c ++) {
				char *name = card_short_name(player->hand[c]);
				mvprintw(player->ty + 1, player->tx + c * 4, "%s", name);
				string_clear(name);
			}

			if (truco->current_player == i)
				attroff(A_REVERSE);
			i ++;
		}

		refresh();

		getch();
	}
}
