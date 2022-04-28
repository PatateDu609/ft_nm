#ifndef NM_H
#define NM_H

#include "defines.h"
#include "structs.h"
#include "core.h"
#include "utils.h"

#include <stdlib.h>

void print_help(t_args *args);
t_args *parse_args(int ac, char **av);
int ft_nm(t_args *args);

#endif
