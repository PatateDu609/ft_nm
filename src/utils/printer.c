#include "utils.h"
#include "structs.h"
#include "ft_getopt.h"

static void __ft_putstr(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

void ft_putstr(char *str)
{
	__ft_putstr(1, str);
}

void ft_putendl(char *str)
{
	__ft_putstr(1, str);
	__ft_putstr(1, "\n");
}

void log_error(char *msg)
{
	__ft_putstr(2, msg);
	__ft_putstr(2, "\n");
}

void log_stat_error(char *name, char *msg)
{
	__ft_putstr(2, "ft_nm: ");
	__ft_putstr(2, name);
	__ft_putstr(2, ": ");
	__ft_putstr(2, msg);
	__ft_putstr(2, "\n");
}

int fatal(char *msg)
{
	log_error(msg);
	return 1;
}

void print_args(t_args *args)
{
	print_strs(args->files);
	print_flags(args->flags, args->options);
}
