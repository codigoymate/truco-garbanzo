#include <ia.h>

#include <player.h>
#include <stdlib.h>
#include <timing.h>

void ia_play(Truco *truco) {
	int i;
	
	Player *player = get_player(truco, truco->current_player);

	/* TODO: improve IA
	*/

	delay(1000);

	for (i = 0; i < 3; i ++) {
		if (player->hand[i]) {
			play_card(player, i);
			return;
		}
	}
}
