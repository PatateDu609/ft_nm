#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <unistd.h>
#include "structs.h"

void free_args(t_args *args);

void print_args(t_args *args);

size_t ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2);
void print_strs(char **strs);

void ft_putstr(char *str);
void ft_putendl(char *str);
void log_error(char *msg);
int fatal(char *msg);

#endif
