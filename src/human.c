#include <human.h>

#include <player.h>
#include <timing.h>

void human_play(Truco *truco, int key) {
    switch (key) {
    case '1':
    case '2':
    case '3':
        if (play_card(truco->first_player, key - '1'))
            next_player(truco);
        break;
    
    case 27:
        truco->exit_stage = 1;
        truco->stage = MAIN_MENU_STAGE;
        break;

    default:
        break;
    }

    delay(100);
}