#include <game_stage.h>

#include <ncurses.h>

void run_game(Truco *truco) {

	Player *player;

    while (1) {
		int i = 0;
		clear();

		for (player = truco->first_player; player != NULL; player = player->next) {
			if (truco->current_player == i) 
				attron(A_REVERSE);
			mvprintw(player->ty, player->tx, "%s", player->name);
			if (truco->current_player == i)
				attroff(A_REVERSE);
			i ++;
		}

		refresh();

		getch();
	}
}
