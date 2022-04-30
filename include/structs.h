#ifndef STRUCTS_H
#define STRUCTS_H

#include "defines.h"
#include <inttypes.h>
#include <elf.h>
#include <stddef.h>

typedef struct s_option
{
	char short_name;
	char *name;
	char *description;
	uint8_t *value;
	uint8_t flag;
} t_option;

typedef struct s_args
{
	char **files;
	char flags;
	int nb_opt;
	t_option *options;
} t_args;

typedef struct s_file_dump
{
	unsigned char class;
	unsigned char *mapping;

	union
	{
		Elf64_Ehdr *elf64;
		Elf32_Ehdr *elf32;
	};
} t_file_dump;

typedef struct s_symbol_x64
{
	char *name;
	uint8_t sect_name;
	Elf64_Addr value;
	Elf64_Xword size;
	uint8_t bind;
	uint8_t type;
	uint8_t visibility;
	Elf64_Word shndx;
	Elf64_Shdr *section;
} t_symbol_x64;

typedef struct s_symbol_x86
{
	char *name;
	uint8_t sect_name;
	Elf32_Addr value;
	Elf32_Word size;
	uint8_t bind;
	uint8_t type;
	uint8_t visibility;
	Elf32_Word shndx;
	Elf32_Shdr *section;
} t_symbol_x86;

typedef struct s_symbol
{
	t_symbol_x64 *x64;
	t_symbol_x86 *x86;
} t_symbol;

typedef struct s_file
{
	int fd;
	char *name;
	t_file_dump *dump;
	t_args *args;
	size_t size;
	t_symbol *symbols;
	int nb_symbols;
} t_file;

typedef struct s_section_to_type
{
	char *name;
	uint8_t type;
	uint8_t exact;
} t_section_to_type;

extern t_section_to_type g_stt[];

#endif
