#ifndef CORE_H
#define CORE_H

#include <elf.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "structs.h"
#include "utils.h"
#include "core_shared.h"

uint8_t check_mag(unsigned char *dump);
void extract_header(t_file_dump *dump);
void nm_64(t_file *file);
void nm_32(t_file *file);

int load_file(t_file *file);
t_file *open_file(char *name);
uint8_t chk_sh_name(Elf64_Word sh_name, char *name, char *shdr);

#endif
