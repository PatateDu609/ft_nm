#include "core.h"

static Elf64_Shdr *get_section(Elf64_Shdr *shdr, Elf64_Section section)
{
	if (SHN_LORESERVE < section && section < SHN_HIRESERVE)
		return (NULL);
	return (shdr + section);
}

static void nm_64_symtab(t_file *file, Elf64_Shdr *sections, Elf64_Shdr *symtab, Elf64_Shdr *strtab, char *shstrtab)
{
	Elf64_Sym *sym;
	char *str;
	size_t i, j;
	size_t max = symtab->sh_size / symtab->sh_entsize;
	char *name;

	i = 1;
	j = 0;
	sym = (Elf64_Sym *)(file->dump->mapping + symtab->sh_offset);
	str = (char *)(file->dump->mapping + strtab->sh_offset);
	file->symbols = malloc(max * sizeof(t_symbol));
	if (!file->symbols)
		return;
	while (i < max)
	{
		Elf64_Shdr *section = get_section(sections, sym[i].st_shndx);
		name = str + sym[i].st_name;
		if (section && (name == NULL || name[0] == '\0'))
			name = shstrtab + section->sh_name;
		if (add_symbol_x64(file->symbols + j++, name,
						   section && name == shstrtab + section->sh_name,
						   &sym[i], section, sym[i].st_shndx))
			return;
		i++;
	}
	file->nb_symbols = j;
	print_syms(file, j);
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
		if (!strtab && shdr[i].sh_type == SHT_STRTAB && chk_sh_name(shdr[i].sh_name, STRTAB, shstrtab))
			strtab = &shdr[i];
		i++;
	}
	if (symtab && strtab)
		nm_64_symtab(file, shdr, symtab, strtab, shstrtab);
	else
	{
		ft_putstr("ft_nm: ");
		ft_putstr(file->name);
		ft_putstr(": No symbol table found\n");
	}
}
