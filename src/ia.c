#include <ia.h>

#include <player.h>
#include <stdlib.h>
#include <time.h>
#include <logger.h>
#include <string_utils.h>

void ia_play(Truco *truco) {
	int i;
	
	Player *player = NULL;

	player = get_player(truco, truco->current_player);

	if (player->surrendered) {
		next_player(truco);
		return ;
	}

	if (clock() < truco->ia_timer) return;


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

void ia_play_canto(Truco *truco) {
	char *msg;
	Player *player = NULL;

	if (clock() < truco->ia_timer) return;

	player = get_player(truco, truco->current_player);

	/* TODO: Quiero/No Quiero */
	truco->canto_mode = 0;

	msg = string_set(NULL, player->name);
	msg = string_cat(msg, ": Quiero !");
	log_print(msg);
	string_clean(msg);

	/* Increment current player */
	truco->current_player ++;
	if (truco->current_player >= truco->player_count) truco->current_player = 0;

	truco->ia_timer = clock() + (CLOCKS_PER_SEC / 1000) * 1000;
}
