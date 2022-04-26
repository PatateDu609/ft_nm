#ifndef FT_GETOPT_H
#define FT_GETOPT_H

#include "structs.h"
#include <stddef.h>
#include <stdlib.h>

int8_t get_option(t_option *options, char *arg);
t_option *init_options(int *nb);
void print_flags(uint8_t flags, t_option *options);

#endif
