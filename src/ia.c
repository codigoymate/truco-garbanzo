#include <ia.h>

#include <player.h>
#include <stdlib.h>

void ia_play(Truco *truco) {
	int i;
	Player *player = get_player(truco, truco->current_player);

	/* TODO: improve IA
	*/

	for (i = 0; i < 3; i ++) {
		if (player->hand[i]) {
			player->played[i] = player->hand[i];
			player->hand[i] = NULL;
			return;
		}
	}
}
