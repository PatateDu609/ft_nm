#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <unistd.h>
#include "structs.h"

void free_file(t_file *file);
void free_args(t_args *args);

void print_args(t_args *args);

char *get_name(t_symbol *sym);

size_t ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2);
int ft_strncmp(char *s1, char *s2, size_t n);
void print_strs(char **strs);

void ft_putstr(char *str);
void ft_putendl(char *str);
void log_error(char *msg);
void log_error_open(char *prefix, char *file);
int fatal(char *msg);

void sort(int rev, t_symbol *syms, int len);

#endif
