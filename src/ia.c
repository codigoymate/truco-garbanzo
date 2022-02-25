#include <ia.h>

#include <player.h>
#include <stdlib.h>
#include <time.h>

void ia_play(Truco *truco) {
	int i;
	
	Player *player = NULL;

	if (clock() < truco->ia_timer) return;
	
	player = get_player(truco, truco->current_player);

	/* TODO: improve IA
	*/

	for (i = 0; i < 3; i ++) {
		if (player->hand[i]) {
			play_card(player, i);

			truco->ia_timer = clock() + (CLOCKS_PER_SEC / 1000) * 1000;

			next_player(truco);
			return;
		}
	}
	
	
}
