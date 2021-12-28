#include <game_stage.h>

#include <ncurses.h>
#include <string_utils.h>
#include <deck.h>

void run_game(Truco *truco) {

    while (1) {
		clear();

		deck_merge(truco->deck);

		card_draw(stdscr, truco->deck[0], 10, 2);

		refresh();

		getch();
	}
}
