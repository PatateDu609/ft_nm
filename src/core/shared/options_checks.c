#include "core_shared.h"

uint8_t check_normal(uint8_t type)
{
	return (type == '?' ||
			type == 'T' ||
			type == 't' ||
			type == 'r' ||
			type == 'd' ||
			type == 'D' ||
			type == 'B' ||
			type == 'b' ||
			type == 'R' ||
			type == 'C' ||
			type == 'c' ||
			type == 'U' ||
			type == 'u' ||
			type == 'W' ||
			type == 'w' ||
			type == 'n');
}

uint8_t check_a(__attribute__((__unused__)) uint8_t type)
{
	return 1;
}

uint8_t check_g(uint8_t type)
{
	return (type == 'U' ||
			type == 'T' ||
			type == 'W' ||
			type == 'B' ||
			type == 'D' ||
			type == 'R' ||
			type == 'C' ||
			type == 'w');
}

uint8_t check_u(uint8_t type)
{
	return (type == 'U' ||
			type == 'u' ||
			type == 'v' ||
			type == 'V' ||
			type == 'w');
}
