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
	for (int i = 0; i < file->nb_symbols; i++)
	{
		free(file->symbols[i].x64);
		free(file->symbols[i].x86);
	}
	free(file->symbols);

	close(file->fd);

	if (file->dump && file->dump->mapping &&
		file->dump->mapping != MAP_FAILED)
		munmap(file->dump->mapping, file->size);
	free(file->dump);
	free(file);
}
