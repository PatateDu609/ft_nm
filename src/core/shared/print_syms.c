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

void print_syms(t_file *file, int max)
{
	int i;
	char *name;
	uint8_t null = 0;
	t_symbol *symbols = file->symbols;
	uint8_t class = symbols[1].x64 ? ELFCLASS64 : ELFCLASS32;

	if (!CHECK_P(file->args->flags))
		sort(CHECK_R(file->args->flags), symbols, max);
	else if (CHECK_R(file->args->flags))
		rev(symbols, max);

	i = 0;
	while (i < max && (!null || symbols[i].x86 || symbols[i].x64))
	{
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
		if (class == ELFCLASS64)
			ft_putinfos_64(symbols[i].x64);
		else
			ft_putinfos_32(symbols[i].x86);
		name = get_name(symbols + i);
		ft_putendl(name ? name : "");
		i++;
	}
}
