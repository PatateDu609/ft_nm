#ifndef CORE_SHARED_H
#define CORE_SHARED_H

#include "structs.h"
#include "utils.h"
#include <stdlib.h>

t_symbol_x64 *create_symbol_x64(char *name, Elf64_Sym *sym, Elf64_Shdr *type, Elf64_Word ndx);
t_symbol_x86 *create_symbol_x86(char *name, Elf32_Sym *sym, Elf32_Shdr *type, Elf32_Word ndx);

int add_symbol_x64(t_symbol *symbol, char *name, Elf64_Sym *sym, Elf64_Shdr *type, Elf64_Word ndx);
int add_symbol_x86(t_symbol *symbol, char *name, Elf32_Sym *sym, Elf32_Shdr *type, Elf32_Word ndx);

char ft_getinfos_32(t_symbol_x86 *sym);
char ft_getinfos_64(t_symbol_x64 *sym);
void print_syms(t_file *file, int max);

uint8_t check_normal(uint8_t type);
uint8_t check_a(uint8_t type);
uint8_t check_g(uint8_t type);
uint8_t check_u(uint8_t type);

#endif
