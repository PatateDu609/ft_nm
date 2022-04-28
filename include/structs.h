#ifndef STRUCTS_H
#define STRUCTS_H

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

typedef struct s_file
{
	int fd;
	char *name;
	t_file_dump *dump;
	size_t size;
} t_file;

#endif
