#include <canto.h>

#include <logger.h>
#include <string_utils.h>

void canto(Truco *truco, Player *player) {
    char *msg;
    int team = player->id % 2;
    if (truco->canto_team == team) {
        /* Team already have truco/retruco/vale-cuatro */
        return ;
    }

    if (truco->current_canto == VALE_CUATRO) {
        /* Cannot sing more than vale-cuatro */
        return ;
    }

    truco->current_canto ++;
    truco->canto_team = team;

    msg = string_set(NULL, player->name);

    switch (truco->current_canto) {
    case TRUCO:
        msg = string_cat(msg, ": ¡truco!");
        break;
    case RETRUCO:
        msg = string_cat(msg, ": ¡quiero retruco!");
        break;
    case VALE_CUATRO:
        msg = string_cat(msg, ": ¡quiero vale cuatro!");
        break;
    }

    log_print(msg);
    string_clean(msg);
}
