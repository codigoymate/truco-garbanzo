#include <points.h>

#include <logger.h>
#include <string_utils.h>

void give_points(Truco *truco, int points, int team) {
    int i = 0;
    Player *player;
    char *msg = NULL;

    for (player = truco->first_player; player; player = player->next) {
        if (i % 2 == team) player->score += points;
        i ++;
    }

    /* Log */
    msg = string_set(msg, "Equipo ");
    msg = string_cat_number(msg, team + 1);
    msg = string_cat(msg, " obtiene ");
    msg = string_cat_number(msg, points);
    if (points > 1) msg = string_cat(msg, "puntos.");
    else msg = string_cat(msg, " punto.");
    log_print(msg);
    string_clean(msg);
}
