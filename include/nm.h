#ifndef NM_H
#define NM_H

#include "defines.h"
#include "structs.h"

#include <stdlib.h>

void print_help(t_args *args);
t_args *parse_args(int ac, char **av);

#endif
