#include <ia.h>

#include <player.h>
#include <stdlib.h>
#include <time.h>
#include <logger.h>
#include <string_utils.h>
#include <random.h>
#include <points.h>

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
	int quiero = 0;

	if (clock() < truco->ia_timer) return;

	player = get_player(truco, truco->current_player);

	
	if (has_low_cards(player)) {
		if (rand_double() < 0.2) quiero = 1;
	} else {
		quiero = 1;
	}

	truco->canto_mode = 0;

	msg = string_set(NULL, player->name);
	if (quiero) msg = string_cat(msg, ": Quiero !");
	else msg = string_cat(msg, ": No quiero");
	log_print(msg);
	string_clean(msg);

	if (!quiero) {
		/* Give points to opponent team */
		give_points(truco, truco->current_canto, !(player->id % 2));
		truco->round_finished = 1;
	} else {
		/* Increment current player */
		truco->current_player ++;
		if (truco->current_player >= truco->player_count) truco->current_player = 0;
	}

	truco->ia_timer = clock() + (CLOCKS_PER_SEC / 1000) * 1000;
}
