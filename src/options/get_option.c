#include "ft_getopt.h"
#include "utils.h"

int8_t get_option(t_option *options, char *arg)
{
	int8_t flag = -1;

	for (int i = 0; options[i].name; i++)
	{
		if (arg[0] == '-' && arg[1] == options[i].short_name)
		{
			flag = options[i].flag;
			break;
		}
		else if (arg[0] == '-' && arg[1] == '-' &&
				 ft_strcmp(arg + 2, options[i].name) == 0)
		{
			flag = options[i].flag;
			break;
		}
	}
	return flag;
}
