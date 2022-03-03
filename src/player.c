#include <player.h>
#include <stdlib.h>
#include <string_utils.h>
#include <logger.h>

Player *player_new(const char *name) {
	int i;
	static int id = 0;
	Player *player = (Player *) malloc(sizeof(Player));

	player->name = string_set(NULL, name);
	player->id = id ++; 
	player->next = NULL;
	player->score = 0;

	player->surrendered = 0;

	for (i = 0; i < 3; i ++) {
		player->hand[i] = NULL;
		player->played[i] = NULL;
	}

	return player;
}

int play_card(Player *player, int index) {
	int fs = 0;
	char *cn, *msg;
	if (player->hand[index]) {

		/* Find a free space on played cards */
		while (player->played[fs] && fs < 3) fs ++;

		/* Move the indexed card to free space */
		player->played[fs] = player->hand[index];
		player->hand[index] = NULL;

		/* Log */
		cn = card_long_name(player->played[fs]);
		msg = string_set(NULL, player->name);
		msg = string_cat(msg, "(");
		msg = string_cat_number(msg, player->id % 2 + 1);
		msg = string_cat(msg, ") juega ");
		msg = string_cat(msg, cn);
		log_print(msg);
		string_clean(cn);
		string_clean(msg);

		return 1; /* Success */
	} else return 0;
}
