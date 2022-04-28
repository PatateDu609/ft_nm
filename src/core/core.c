#include "core.h"
#include "utils.h"

t_file *open_file(char *name)
{
	t_file *file;
	struct stat s;

	file = (t_file *)malloc(sizeof(t_file));
	file->fd = open(name, O_RDONLY);
	file->name = name;
	file->size = fstat(file->fd, &s) ? 0 : s.st_size;
	file->dump = NULL;
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
