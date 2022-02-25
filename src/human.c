#include <human.h>

#include <player.h>
#include <time.h>

void human_play(Truco *truco, int key) {
    switch (key) {
    case '1':
    case '2':
    case '3':
        if (play_card(truco->first_player, key - '1')) {
            truco->ia_timer = clock() + (CLOCKS_PER_SEC / 1000) * 1000;
            next_player(truco);
        }
        break;

    default:
        break;
    }

}