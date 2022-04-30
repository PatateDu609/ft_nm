#include "core.h"

static Elf32_Shdr *get_section(Elf32_Shdr *shdr, Elf32_Section section)
{
	if (SHN_LORESERVE < section && section < SHN_HIRESERVE)
		return (NULL);
	return (shdr + section);
}

static void nm_32_symtab(t_file *file, Elf32_Shdr *sections, Elf32_Shdr *symtab, Elf32_Shdr *strtab, char *shstrtab)
{
	Elf32_Sym *sym;
	char *str;
	size_t i, j;
	size_t max = symtab->sh_size / symtab->sh_entsize;
	char *name;

	i = 1;
	j = 0;
	sym = (Elf32_Sym *)(file->dump->mapping + symtab->sh_offset);
	str = (char *)(file->dump->mapping + strtab->sh_offset);
	file->symbols = malloc(max * sizeof(t_symbol));
	if (!file->symbols)
		return;
	while (i < max)
	{
		Elf32_Shdr *section = get_section(sections, sym[i].st_shndx);
		name = str + sym[i].st_name;
		if (section && (name == NULL || name[0] == '\0'))
			name = shstrtab + section->sh_name;
		if (add_symbol_x86(file->symbols + j++, name,
						   section && name == shstrtab + section->sh_name,
						   &sym[i], section, sym[i].st_shndx))
			return;
		i++;
	}
	file->nb_symbols = j;
	print_syms(file, j);
}

void nm_32(t_file *file)
{
	Elf32_Shdr *shdr;
	char *shstrtab;
	t_file_dump *dump = file->dump;
	Elf32_Shdr *symtab = NULL;
	Elf32_Shdr *strtab = NULL;
	int i;

	shdr = (Elf32_Shdr *)(dump->mapping + dump->elf32->e_shoff);
	shstrtab = (char *)(file->dump->mapping + shdr[dump->elf32->e_shstrndx].sh_offset);
	i = 0;
	while (i < dump->elf32->e_shnum)
	{
		if (!symtab && shdr[i].sh_type == SHT_SYMTAB)
			symtab = &shdr[i];
		if (!strtab && shdr[i].sh_type == SHT_STRTAB && chk_sh_name(shdr[i].sh_name, STRTAB, shstrtab))
			strtab = &shdr[i];
		i++;
	}
	if (symtab && strtab)
		nm_32_symtab(file, shdr, symtab, strtab, shstrtab);
	else
	{
		ft_putstr("ft_nm: ");
		ft_putstr(file->name);
		ft_putstr(": No symbol table found\n");
	}
}
