#include "utils.h"
#include <stdlib.h>
#include <sys/mman.h>

void free_args(t_args *args)
{
	free(args->files);
	free(args);
}

void free_file(t_file *file)
{
	if (file->dump && file->dump->mapping &&
		file->dump->mapping != MAP_FAILED)
		munmap(file->dump->mapping, file->size);
	free(file->dump);
	free(file);
}
