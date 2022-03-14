#include <deck.h>
#include <stdlib.h>

void deck_init(Card *deck[]) {

	deck[0] = card_new(4, ORO, 0);
	deck[1] = card_new(4, COPAS, 0);
	deck[2] = card_new(4, ESPADAS, 0);
	deck[3] = card_new(4, BASTOS, 0);

	deck[4] = card_new(5, ORO, 1);
	deck[5] = card_new(5, COPAS, 1);
	deck[6] = card_new(5, ESPADAS, 1);
	deck[7] = card_new(5, BASTOS, 1);

	deck[8] = card_new(6, ORO, 2);
	deck[9] = card_new(6, COPAS, 2);
	deck[10] = card_new(6, ESPADAS, 2);
	deck[11] = card_new(6, BASTOS, 2);

	deck[12] = card_new(7, COPAS, 3);
	deck[13] = card_new(7, BASTOS, 3);

	deck[14] = card_new(10, ORO, 4);
	deck[15] = card_new(10, COPAS, 4);
	deck[16] = card_new(10, ESPADAS, 4);
	deck[17] = card_new(10, BASTOS, 4);

	deck[18] = card_new(11, ORO, 5);
	deck[19] = card_new(11, COPAS, 5);
	deck[20] = card_new(11, ESPADAS, 5);
	deck[21] = card_new(11, BASTOS, 5);

	deck[22] = card_new(12, ORO, 6);
	deck[23] = card_new(12, COPAS, 6);
	deck[24] = card_new(12, ESPADAS, 6);
	deck[25] = card_new(12, BASTOS, 6);

	deck[26] = card_new(1, ORO, 7);
	deck[27] = card_new(1, COPAS, 7);

	deck[28] = card_new(2, ORO, 8);
	deck[29] = card_new(2, COPAS, 8);
	deck[30] = card_new(2, ESPADAS, 8);
	deck[31] = card_new(2, BASTOS, 8);

	deck[32] = card_new(3, ORO, 9);
	deck[33] = card_new(3, COPAS, 9);
	deck[34] = card_new(3, ESPADAS, 9);
	deck[35] = card_new(3, BASTOS, 9);

	deck[36] = card_new(7, ORO, 10);
	deck[37] = card_new(7, ESPADAS, 11);

	deck[38] = card_new(1, BASTOS, 12);
	deck[39] = card_new(1, ESPADAS, 13);

	/* The null card */
	deck[40] = card_new(-1, -1, -1);
}

void deck_clean(Card *deck[]) {
	int i;

	for (i = 0; i < 40; i ++) {
		free(deck[i]);
	}
}

void deck_merge(Card *deck[]) {
	int i, r;
	Card *tmp;
	for (i = 0; i < 40; i ++) {
		r = rand() % 40;
		tmp = deck[i];
		deck[i] = deck[r];
		deck[r] = tmp;
	}
}

void deal_cards(Truco *truco) {
	int deck_index = 0;
	Player *player;

	for (player = truco->first_player; player != NULL; player = player->next) {
		int i = 0;
		/* Reset the player and deal cards */
		player->surrendered = 0;
		for (i = 0; i < 3; i ++) {
			player->hand[i] = truco->deck[deck_index];
			player->played[i] = NULL;
			deck_index ++;
		}
	}

}
