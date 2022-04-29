#include "ft_getopt.h"

static void init_help(t_option *option)
{
	option->name = "help";
	option->short_name = 'h';
	option->description = "Display this help message and exit.";
	option->value = NULL;
	option->flag = OPT_H;
}

static void init_g(t_option *option)
{
	option->name = "extern-only";
	option->short_name = 'g';
	option->description = "Display only external symbols.";
	option->value = NULL;
	option->flag = OPT_G;
}

static void init_a(t_option *option)
{
	option->name = "debug-syms";
	option->short_name = 'a';
	option->description = "Display debug symbols.";
	option->value = NULL;
	option->flag = OPT_A;
}

static void init_u(t_option *option)
{
	option->name = "undefined-only";
	option->short_name = 'u';
	option->description = "Display only undefined symbols.";
	option->value = NULL;
	option->flag = OPT_U;
}

static void init_p(t_option *option)
{
	option->name = "no-sort";
	option->short_name = 'p';
	option->description = "Do not sort output.";
	option->value = NULL;
	option->flag = OPT_P;
}

static void init_r(t_option *option)
{
	option->name = "reverse-sort";
	option->short_name = 'r';
	option->description = "Reverse sort output.";
	option->value = NULL;
	option->flag = OPT_R;
}

t_option *init_options(int *nb)
{
	*nb = 6;
	if (!*nb)
		return NULL;
	t_option *options = malloc(sizeof(t_option) * *nb);
	if (!options)
		return NULL;
	init_help(&options[0]);
	init_g(&options[1]);
	init_a(&options[2]);
	init_u(&options[3]);
	init_p(&options[4]);
	init_r(&options[5]);

	return options;
}
