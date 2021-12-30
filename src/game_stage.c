#include <game_stage.h>

#include <ncurses.h>
#include <string_utils.h>
#include <deck.h>

void run_game(Truco *truco) {

	/*Player *player;*/

    while (1) {
		int i = 0, x = 1, y = 1;
		clear();

		/*for (player = truco->first_player; player != NULL; player = player->next) {
			if (truco->current_player == i) 
				attron(A_REVERSE);
			mvprintw(player->ty, player->tx, "%s", player->name);
			if (truco->current_player == i)
				attroff(A_REVERSE);
			i ++;
		}*/

		deck_merge(truco->deck);

		for (i = 0; i < 40; i ++) {
			char *name = card_long_name(truco->deck[i]);
			mvprintw(y, x, "%s", name); y ++;
			if (y > 20) { y = 1; x = 40; }
			string_clear(name);
		}

		refresh();

		getch();
	}
}
