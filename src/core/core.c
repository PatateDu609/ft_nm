#include "core.h"
#include "utils.h"

t_file *open_file(char *name)
{
	t_file *file;
	struct stat s;
	int fd = open(name, O_RDONLY);

	if (fd == -1)
	{
		log_stat_error(name, "No such file");
		return (NULL);
	}
	int ret = fstat(fd, &s);
	if (ret == -1)
		return (NULL);
	if (S_ISDIR(s.st_mode))
	{
		log_stat_error(name, "Is a directory");
		return (NULL);
	}

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
	{
		log_error("ft_nm: Malloc failed...");
		return NULL;
	}
	file->fd = fd;
	file->name = name;
	file->size = s.st_size;
	file->dump = NULL;
	file->args = NULL;
	file->nb_symbols = 0;
	file->symbols = NULL;
	return (file);
}

int load_file(t_file *file)
{
	t_file_dump *dump;

	dump = (t_file_dump *)malloc(sizeof(t_file_dump));
	dump->mapping = mmap(NULL, file->size, PROT_READ, MAP_PRIVATE, file->fd, 0);
	if (dump->mapping == MAP_FAILED)
	{
		log_error("ft_nm: mmap failed");
		return (-1);
	}
	if (!check_mag(dump->mapping))
	{
		log_error("ft_nm: invalid file");
		return (-1);
	}
	extract_header(dump);
	if (!dump->elf32 && !dump->elf64)
		return (-1);
	file->dump = dump;
	return (0);
}
