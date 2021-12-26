#include <game_stage.h>

#include <ncurses.h>

void run_game(Truco *truco) {

	Player *player;

    while (1) {
		clear();

		for (player = truco->first_player; player != NULL; player = player->next) {
			printw("%s\n", player->name);
		}

		refresh();

		getch();
	}
}
