#include "get_next_line.h"

typedef struct list
{
    int *buffer;
    size_t len_buffer;
    size_t cap_buffer;
} LIST;

LIST *ft_list(size_t cap)
{
    LIST *lst;

    lst = malloc(sizeof(LIST));
    lst->len_buffer = 0;
    lst->cap_buffer = cap;
    lst->buffer = malloc(sizeof(int) * cap);
    return (lst);
}

int find(LIST *lst, int number)
{
    int index;

    index = 0;
    while (lst->len_buffer > index)
    {
        if (lst->buffer[index] == number)
            return (index);
        index++;
    }
    return (-1);
}

void expand_lst(LIST *lst)
{
    int *expand;
    int index;

    index = 0;
    expand = malloc(sizeof(int) * (2 * lst->cap_buffer));
    lst->cap_buffer *= 2;
    while (lst->len_buffer > index)
    {
        expand[index] = lst->buffer[index];
        index++;
    }
    free(lst->buffer);
    lst->buffer = expand;
}

void insert(LIST *lst, int count)
{
    if (lst->len_buffer >= lst->cap_buffer)
        expand_lst(lst);
    lst->buffer[lst->len_buffer] = count;
    lst->len_buffer++;
}

void pop(LIST *lst)
{
    lst->len_buffer--;
}

void print_list(LIST *lst)
{
    int count;

    count = 0;
    printf("cap = %ld\n", lst->cap_buffer);
    printf("len = %ld\n", lst->len_buffer);
    printf("[ ");
    while (count < lst->len_buffer)
    {
        printf("%d, ", lst->buffer[count++]);
    }
    printf("]\n");
}

int main(void)
{
    LIST *ret;

    ret = ft_list(3);
    insert(ret, 6);
    insert(ret, -3);
    insert(ret, -4);
    insert(ret, 9);
    printf("%d\n", find(ret, 9));
    // pop(ret);
    print_list(ret);
}