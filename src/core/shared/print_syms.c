#include "core_shared.h"

void ft_puthex(Elf64_Addr addr, int print, int size)
{
	char *hex;
	char rev[16];
	int i;

	hex = "0123456789abcdef";
	i = 0;
	while (i < size)
	{
		rev[size - i - 1] = print ? hex[addr % 16] : ' ';
		addr /= 16;
		i++;
	}
	write(1, rev, size);
}

static uint8_t should_continue(char flags, char type)
{
	uint8_t g = CHECK_G(flags);
	uint8_t u = CHECK_U(flags);
	uint8_t a = CHECK_A(flags);

	if (u)
		return (check_u(type));
	if (g)
		return (check_g(type));
	if (a)
		return (check_a(type));
	return (check_normal(type));
}

void print_syms(t_file *file, int max)
{
	int i;
	char *name;
	uint8_t null = 0;
	t_symbol *symbols = file->symbols;
	uint8_t class = symbols[1].x64 ? ELFCLASS64 : ELFCLASS32;
	char type;

	if (!CHECK_P(file->args->flags))
		sort(CHECK_R(file->args->flags), symbols, max);

	i = 0;
	while (i < max && (!null || symbols[i].x86 || symbols[i].x64))
	{
		if (class == ELFCLASS64)
			type = ft_getinfos_64(file, symbols[i].x64);
		else
			type = ft_getinfos_32(file, symbols[i].x86);

		if (!should_continue(file->args->flags, type))
		{
			i++;
			continue;
		}

		if (symbols[i].x64)
			ft_puthex(symbols[i].x64->value, symbols[i].x64->shndx != SHN_UNDEF, 16);
		else if (symbols[i].x86)
			ft_puthex(symbols[i].x86->value, symbols[i].x86->shndx != SHN_UNDEF, 8);
		else
		{
			null = 1;
			ft_puthex(0, 1, class == ELFCLASS64 ? 16 : 8);
		}
		ft_putstr(" ");
		write(1, &type, 1);
		ft_putstr(" ");
		name = get_name(symbols + i);
		ft_putendl(name ? name : "");
		i++;
	}
}
