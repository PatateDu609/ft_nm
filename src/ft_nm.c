#include "nm.h"

int ft_nm(t_args *args)
{
	t_file *file;
	int ret = 0;
	uint8_t print_prefix = !!args->files[1];

	for (char **pfile = args->files; *pfile; pfile++)
	{
		char *f = *pfile;
		file = open_file(f);
		if (!file)
		{
			ret++;
			continue;
		}
		file->args = args;
		if (load_file(file) == -1)
		{
			ret++;
			free_file(file);
			continue;
		}
		if (print_prefix)
		{
			ft_putendl("");
			ft_putstr(f);
			ft_putendl(":");
		}
		if (file->dump->class == ELFCLASS64)
			nm_64(file);
		else if (file->dump->class == ELFCLASS32)
			nm_32(file);
		else
		{
			ret++;
			log_error("ft_nm: Unsupported class");
			free_file(file);
			continue;
		}
		free_file(file);
	}
	return (ret);
}
