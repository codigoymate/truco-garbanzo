#ifndef LOGGER_H
#define LOGGER_H

#include <truco.h>

void log_init(Truco *truco);
void log_clean(Truco *truco);

void log_print(Truco *truco, char *str);

#endif
