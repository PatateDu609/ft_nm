#include "structs.h"

t_section_to_type g_stt[] = {
	{".bss", 'b', 1},
	{".debug", 'N', 1},
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
