#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#define MAX_FD 1024
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct t_list
{
    char *buffer;
    size_t len_buffer;
    size_t cap_buffer;
} t_LIST;

char *get_next_line(int fd);
char *lst_find(t_LIST *lst, char number);
int lst_expand(t_LIST *lst);
char *lst_getslice(t_LIST *lst, size_t start, size_t end);
void *ft_memmove(void *dest, const void *src, size_t n);

#endif
