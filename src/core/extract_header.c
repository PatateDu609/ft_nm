#include "core.h"

uint8_t check_mag(unsigned char *dump)
{
	return !ft_strncmp((char *)dump, ELFMAG, SELFMAG);
}

void extract_header(t_file_dump *dump)
{
	dump->class = dump->mapping[EI_CLASS];
	if (dump->class == ELFCLASS32)
		dump->elf32 = (Elf32_Ehdr *)dump->mapping;
	else if (dump->class == ELFCLASS64)
		dump->elf64 = (Elf64_Ehdr *)dump->mapping;
	else
	{
		dump->elf32 = NULL; // puts both elf to 0 (union)
		log_error("ft_nm: Unknown class");
	}
}
