#include <points.h>

void give_points(Truco *truco, int points, int team) {
    int i = 0;
    Player *player;

    for (player = truco->first_player; player; player = player->next) {
        if (i % 2 == team) player->score += points;
        i ++;
    }
}
