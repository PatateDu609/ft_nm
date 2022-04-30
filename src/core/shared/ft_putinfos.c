#include "core_shared.h"

char ft_getinfos_64(t_symbol_x64 *sym)
{
	char c;
	if (!sym || sym->shndx == SHN_ABS)
		c = 'A';
	else if (sym->section->sh_type == SHT_NOBITS)
		c = 'B';
	else if (sym->bind == STB_WEAK && sym->type == STT_OBJECT)
		c = sym->shndx == SHN_UNDEF ? 'v' : 'V';
	else if (sym->bind == STB_WEAK)
		c = sym->shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym->shndx == SHN_UNDEF)
		c = 'U';
	else if (sym->bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (sym->shndx == SHN_COMMON)
		c = 'C';
	else if (sym->section->sh_flags == SHF_ALLOC)
		c = 'R';
	else if (sym->section->sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if ((sym->section->sh_type == SHT_PROGBITS &&
			  sym->section->sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) ||
			 sym->section->sh_type == SHT_INIT_ARRAY ||
			 sym->section->sh_type == SHT_FINI_ARRAY ||
			 sym->section->sh_type == SHT_PREINIT_ARRAY)
		c = 'T';
	else
		c = '?';
	if ((!sym || sym->bind == STB_LOCAL) && c != '?')
		c += 32;
	// write(1, &c, 1);
	// write(1, " ", 1);
	return c;
}

char ft_getinfos_32(t_symbol_x86 *sym)
{
	char c;
	if (!sym || sym->shndx == SHN_ABS)
		c = 'A';
	else if (sym->section->sh_type == SHT_NOBITS)
		c = 'B';
	else if (sym->bind == STB_WEAK && sym->type == STT_OBJECT)
		c = sym->shndx == SHN_UNDEF ? 'v' : 'V';
	else if (sym->bind == STB_WEAK)
		c = sym->shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym->shndx == SHN_UNDEF)
		c = 'U';
	else if (sym->bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (sym->shndx == SHN_COMMON)
		c = 'C';
	else if (sym->section->sh_flags == SHF_ALLOC)
		c = 'R';
	else if (sym->section->sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if ((sym->section->sh_type == SHT_PROGBITS &&
			  sym->section->sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) ||
			 sym->section->sh_type == SHT_INIT_ARRAY ||
			 sym->section->sh_type == SHT_FINI_ARRAY ||
			 sym->section->sh_type == SHT_PREINIT_ARRAY)
		c = 'T';
	else
		c = '?';
	if ((!sym || sym->bind == STB_LOCAL) && c != '?')
		c += 32;
	// write(1, &c, 1);
	// write(1, " ", 1);
	return c;
}
