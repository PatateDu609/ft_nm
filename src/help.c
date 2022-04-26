#include "utils.h"

void print_help(t_args *args)
{
	if (!args->nb_opt)
		ft_putstr("Usage: nm [files(s)]\n");
	else
		ft_putstr("Usage: nm [option(s)] [files(s)]\n");
	ft_putstr(" List symbols in [files(s)] (a.out by default).\n");
	if (!args->nb_opt)
		return;
	ft_putstr(" The options are:\n");
	for (int i = 0; i < args->nb_opt; i++)
	{
		ft_putstr("\t-");
		write(1, &args->options[i].short_name, 1);
		ft_putstr(", --");
		ft_putstr(args->options[i].name);
		ft_putstr("\n\t");
		ft_putendl(args->options[i].description);
		ft_putstr("\n");
	}
}
