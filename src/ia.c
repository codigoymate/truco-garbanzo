#include <ia.h>

#include <player.h>
#include <stdlib.h>
#include <logger.h>
#include <string_utils.h>

void ia_play(Truco *truco) {
	int i;
	char *cn, *msg;
	Player *player = get_player(truco, truco->current_player);

	/* TODO: improve IA
	*/

	for (i = 0; i < 3; i ++) {
		if (player->hand[i]) {
			play_card(player, i);

			/* Log */
			cn = card_long_name(player->played[i]);
			msg = string_set(NULL, player->name);
			msg = string_cat(msg, " juega ");
			msg = string_cat(msg, cn);
			log_print(truco, msg);
			string_clean(cn);
			string_clean(msg);
			return;
		}
	}
}
