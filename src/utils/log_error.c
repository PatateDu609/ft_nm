#include "utils.h"

void log_error_open(char *prefix, char *file)
{
    ft_putstr(prefix);
    ft_putstr(file);
    ft_putendl(": Error opening file");
}
