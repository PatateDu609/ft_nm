#include "core_shared.h"

static char undef_x64(t_symbol_x64 *sym)
{
	if (sym->bind == STB_WEAK)
		return sym->type == STT_OBJECT ? 'v' : 'w';
	return 'U';
}

static char section_to_type_x64(char *name)
{
	for (int i = 0; g_stt[i].name; i++)
	{
		if (g_stt[i].exact && !ft_strcmp(name, g_stt[i].name))
			return g_stt[i].type;
		else if (!g_stt[i].exact && ft_strstr(name, g_stt[i].name))
			return g_stt[i].type;
	}

	return '?';
}

static char decode_section_type_x64(t_symbol_x64 *sym)
{
	if (sym->type == STT_FUNC || sym->section->sh_flags & SHF_EXECINSTR)
		return 't';

	if (sym->section->sh_type == SHT_PROGBITS ||
		sym->section->sh_type == SHT_HASH ||
		sym->section->sh_type == SHT_NOTE ||
		sym->section->sh_type == SHT_INIT_ARRAY ||
		sym->section->sh_type == SHT_FINI_ARRAY ||
		sym->section->sh_type == SHT_PREINIT_ARRAY ||
		sym->section->sh_type == SHT_GNU_LIBLIST ||
		sym->section->sh_type == SHT_GNU_HASH ||
		sym->section->sh_type == SHT_DYNAMIC)
	{
		if (!(sym->section->sh_flags & SHF_WRITE))
			return 'r';
		else if (sym->section->sh_flags & SHF_COMPRESSED)
			return 'g';
		else
			return 'd';
	}

	if (sym->section->sh_flags & SHF_ALLOC)
	{
		if (sym->section->sh_flags & SHF_COMPRESSED)
			return 's';
		else
			return 'b';
	}

	if (sym->section->sh_offset && !(sym->section->sh_flags & SHF_WRITE))
		return 'n';

	return '?';
}

static char non_abs_x64(t_file *file, t_symbol_x64 *sym)
{
	Elf64_Ehdr *elf64 = file->dump->elf64;
	Elf64_Shdr *section = sym->section;
	Elf64_Shdr *shs = (Elf64_Shdr *)(file->dump->mapping + elf64->e_shoff);
	char *str = (char *)(file->dump->mapping + shs[elf64->e_shstrndx].sh_offset);

	if (!SH_IN(file->dump->mapping, section, file->size))
		return '?';
	char *name = str + section->sh_name;
	char c = section_to_type_x64(name);
	return c == '?' ? decode_section_type_x64(sym) : c;
}

char ft_getinfos_64(t_file *file, t_symbol_x64 *sym)
{
	char c = '?';

	if (sym->shndx == SHN_COMMON)
		c = 'C';
	else if (sym->shndx == SHN_UNDEF)
		c = undef_x64(sym);
	else if (sym->type == STT_GNU_IFUNC)
		c = 'i';
	else if (sym->bind == STB_WEAK)
		c = (sym->type == STT_OBJECT) ? 'V' : 'W';
	else if (sym->bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (sym->shndx != SHN_ABS)
		c = non_abs_x64(file, sym);
	else if (sym->shndx == SHN_ABS)
		c = 'a';
	if (sym->bind == STB_GLOBAL)
		if ('a' <= c && c <= 'z')
			c -= 32;
	return c;
}

char ft_getinfos_32(__attribute_maybe_unused__ t_file *file, __attribute_maybe_unused__ t_symbol_x86 *sym)
{
	char c = '?';
	return c;
}
