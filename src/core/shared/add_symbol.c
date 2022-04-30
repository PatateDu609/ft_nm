#include "core_shared.h"

static t_symbol_x64 *create_symbol_x64(char *name, uint8_t sect_name, Elf64_Sym *sym, Elf64_Shdr *section, Elf64_Word ndx)
{
	t_symbol_x64 *symbol = malloc(sizeof(t_symbol_x64));
	if (!symbol)
		return (NULL);
	symbol->name = name;
	symbol->value = sym->st_value;
	symbol->size = sym->st_size;
	symbol->bind = ELF64_ST_BIND(sym->st_info);
	symbol->type = ELF64_ST_TYPE(sym->st_info);
	symbol->visibility = ELF64_ST_VISIBILITY(sym->st_other);
	symbol->shndx = ndx;
	symbol->section = section;
	symbol->sect_name = sect_name;
	return (symbol);
}

int add_symbol_x64(t_symbol *symbol, char *name, uint8_t sect_name, Elf64_Sym *sym, Elf64_Shdr *section, Elf64_Word ndx)
{
	t_symbol_x64 *x64 = create_symbol_x64(name, sect_name, sym, section, ndx);
	if (!x64)
		return (1);
	symbol->x64 = x64;
	symbol->x86 = NULL;
	return (0);
}

t_symbol_x86 *create_symbol_x86(char *name, uint8_t sect_name, Elf32_Sym *sym, Elf32_Shdr *section, Elf32_Word ndx)
{
	t_symbol_x86 *symbol = malloc(sizeof(t_symbol_x86));
	if (!symbol)
		return (NULL);
	symbol->name = name;
	symbol->value = sym->st_value;
	symbol->size = sym->st_size;
	symbol->bind = ELF32_ST_BIND(sym->st_info);
	symbol->type = ELF32_ST_TYPE(sym->st_info);
	symbol->visibility = ELF32_ST_VISIBILITY(sym->st_other);
	symbol->shndx = ndx;
	symbol->section = section;
	symbol->sect_name = sect_name;
	return (symbol);
}

int add_symbol_x86(t_symbol *symbol, char *name, uint8_t sect_name, Elf32_Sym *sym, Elf32_Shdr *section, Elf32_Word ndx)
{
	t_symbol_x86 *x86 = create_symbol_x86(name, sect_name, sym, section, ndx);
	if (!x86)
		return (1);
	symbol->x64 = NULL;
	symbol->x86 = x86;
	return (0);
}
