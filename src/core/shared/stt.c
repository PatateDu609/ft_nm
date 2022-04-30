#include "core_shared.h"

t_section_to_type g_stt[] = {
	{".bss", 'b', 1},
	{".debug", 'N', 0},
	{"DEBUG", 'N', 0},
	{".drectve", 'i', 1},
	{".edata", 'e', 1},
	{".fini", 't', 1},
	{".idata", 'i', 1},
	{".init", 't', 1},
	{".pdata", 'p', 1},
	{".rdata", 'r', 1},
	{".rodata", 'r', 1},
	{".sbss", 's', 1},
	{".scommon", 'c', 1},
	{".sdata", 'g', 1},
	{"vars", 'd', 0},
	{"zerovars", 'b', 0},
	{0, 0, 1}};

char section_to_type(char *name)
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
