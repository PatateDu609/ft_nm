#include "nm.h"

void nm_64_symtab(t_file *file, Elf64_Shdr *symtab, Elf64_Shdr *strtab)
{
	Elf64_Sym *sym;
	char *str;
	size_t i;
	size_t max = symtab->sh_size / symtab->sh_entsize;

	i = 0;
	sym = (Elf64_Sym *)(file->dump->mapping + symtab->sh_offset);
	str = (char *)(file->dump->mapping + strtab->sh_offset);
	while (i < max)
	{
		if (sym[i].st_name)
			ft_putendl(str + sym[i].st_name);
		i++;
	}
}

void nm_64(t_file *file)
{
	Elf64_Shdr *shdr;
	char *shstrtab;
	t_file_dump *dump = file->dump;
	Elf64_Shdr *symtab = NULL;
	Elf64_Shdr *strtab = NULL;
	int i;

	shdr = (Elf64_Shdr *)(dump->mapping + dump->elf64->e_shoff);
	shstrtab = (char *)(file->dump->mapping + shdr[dump->elf64->e_shstrndx].sh_offset);
	i = 0;
	while (i < dump->elf64->e_shnum)
	{
		if (!symtab && shdr[i].sh_type == SHT_SYMTAB)
			symtab = &shdr[i];
		if (!strtab && shdr[i].sh_type == SHT_STRTAB && chk_sh_name_64(shdr[i].sh_name, ".strtab", shstrtab))
			strtab = &shdr[i];
		i++;
	}
	if (symtab && strtab)
		nm_64_symtab(file, symtab, strtab);
}

int ft_nm(t_args *args)
{
	t_file *file;

	for (char **pfile = args->files; *pfile; pfile++)
	{
		char *f = *pfile;
		file = open_file(f);
		if (file->fd == -1)
		{
			log_error_open("ft_nm: ", f);
			free_file(file);
			continue;
		}
		if (load_file(file) == -1)
		{
			close(file->fd);
			free_file(file);
			continue;
		}
		if (file->dump->class == ELFCLASS64)
			nm_64(file);
		close(file->fd);
		free_file(file);
	}
	return (0);
}
