#include "core.h"

uint8_t chk_sh_name_64(Elf64_Word sh_name, char *name, char *shstrtab)
{
	char *sh_name_str;

	sh_name_str = (char *)(shstrtab + sh_name);
	return !ft_strcmp(sh_name_str, name);
}
