#include "ft_getopt.h"
#include "utils.h"

void print_flags(uint8_t flags, t_option *options)
{
	int i;

	i = 0;
	while (options && options[i].name)
	{
		if (flags & options[i].flag)
		{
			ft_putstr(" - ");
			ft_putstr(options[i].name);
			ft_putstr(" - ");
			ft_putstr(options[i].description);
			ft_putstr(" - ");
			write(1, &options[i].short_name, 1);
			ft_putstr("\n");
		}
		i++;
	}
}
