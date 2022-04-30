#include "utils.h"

char *get_name(t_symbol *sym)
{
	if (!sym->x86 && !sym->x64)
		return (NULL);
	return sym->x86 ? sym->x86->name : sym->x64->name;
}

int ft_valcmp(t_symbol *a, t_symbol *b)
{
	if (a->x64 && b->x64)
		return (a->x64->value > b->x64->value ? 1 : -1);
	if (a->x86 && b->x86)
		return (a->x86->value > b->x86->value ? 1 : -1);
	return 0;
}

static int cmp_symbol(t_symbol *a, t_symbol *b)
{
	if (get_name(a) == NULL || get_name(b) == NULL)
		return (0);
	int ret_str = ft_strcmp_alpha(get_name(a), get_name(b));
	if (ret_str)
		return ret_str;
	if ((ret_str = ft_strcmp(get_name(a), get_name(b))) > 0)
		return ft_valcmp(b, a);
	return ft_valcmp(a, b);
}

static void swap_symbols(t_symbol *a, t_symbol *b)
{
	t_symbol tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int pivot(int rev, t_symbol *symbols, int start, int end)
{
	int i;
	t_symbol *pivot;

	i = start - 1;
	pivot = symbols + end;
	for (int j = start; j < end; j++)
	{
		if ((rev == 1 && cmp_symbol(symbols + j, pivot) < 0) ||
			(rev == -1 && cmp_symbol(symbols + j, pivot) >= 0))
		{
			i++;
			swap_symbols(symbols + i, symbols + j);
		}
	}
	swap_symbols(symbols + i + 1, symbols + end);
	return (i + 1);
}

void __sort(int rev, t_symbol *symbols, int s, int e)
{
	int p;

	if (s < e)
	{
		p = pivot(rev, symbols, s, e);
		__sort(rev, symbols, s, p - 1);
		__sort(rev, symbols, p + 1, e);
	}
}

void sort(int rev, t_symbol *syms, int len)
{
	__sort(rev ? -1 : 1, syms, 0, len - 1);
}
