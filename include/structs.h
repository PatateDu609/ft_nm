#ifndef STRUCTS_H
#define STRUCTS_H

#include <inttypes.h>

typedef struct s_option
{
	char short_name;
	char *name;
	char *description;
	uint8_t *value;
	uint8_t flag;
} t_option;

typedef struct s_args
{
	char **files;
	char flags;
	int nb_opt;
	t_option *options;
} t_args;

#endif
