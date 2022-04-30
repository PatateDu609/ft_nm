#include "utils.h"

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
	{
		if (i == n - 1)
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

size_t ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strstr(char *str, char *to_find)
{
	size_t i;
	size_t j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && to_find[j] && str[i + j] == to_find[j])
			j++;
		if (to_find[j] == '\0')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

void print_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		ft_putstr(" - ");
		ft_putendl(strs[i]);
		i++;
	}
}
