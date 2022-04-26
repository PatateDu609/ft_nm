#include "utils.h"
#include <stdlib.h>

void free_args(t_args *args)
{
	free(args->files);
	free(args);
}
