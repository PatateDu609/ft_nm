#include "nm.h"

int ft_nm(t_args *args)
{
	t_file *file;
	int ret = 0;

	for (char **pfile = args->files; *pfile; pfile++)
	{
		char *f = *pfile;
		file = open_file(f);
		file->args = args;
		if (file->fd == -1)
		{
			log_error_open("ft_nm: ", f);
			free_file(file);
			ret++;
			continue;
		}
		if (load_file(file) == -1)
		{
			ret++;
			close(file->fd);
			free_file(file);
			continue;
		}
		if (file->dump->class == ELFCLASS64)
			nm_64(file);
		else if (file->dump->class == ELFCLASS32)
			nm_32(file);
		else
		{
			ret++;
			log_error("ft_nm: Unsupported class");
			close(file->fd);
			free_file(file);
			continue;
		}
		close(file->fd);
		free_file(file);
	}
	return (ret);
}
