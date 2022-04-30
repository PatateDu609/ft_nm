#include "nm.h"
#include "utils.h"

int main(int ac, char **av)
{
	t_args *args = parse_args(ac, av);

	if (!args)
		return (fatal("An error occured while parsing arguments"));
	else if (args == (void *)-1)
		return (1);

	if (CHECK_H(args->flags))
	{
		print_help(args);
		return (0);
	}
	int ret = ft_nm(args);
	free_args(args);
	return (ret);
}
