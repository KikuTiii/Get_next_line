#include "get_next_line.h"

char *memslice(char *newline, t_LIST *lst, char *line)
{
	line = lst_getslice(lst, 0, newline - lst->buffer);
	if (line == NULL)
		return (NULL);
	lst->len_buffer -= (newline + 1) - lst->buffer;
	ft_memmove(lst->buffer, newline + 1, lst->len_buffer);
	return (line);
}

char *lastmove(t_LIST *lst, char *line)
{
	if (lst->len_buffer > 0)
	{
		line = lst_getslice(lst, 0, lst->len_buffer);
		if (line == NULL)
			return (NULL);
		free(lst->buffer);
		lst->buffer = NULL;
		lst->len_buffer = 0;
		lst = 0;
		return (line);
	}
	free(lst->buffer);
	return (NULL);
}

char *lst_create(t_LIST *lst)
{
	if (lst->buffer == NULL)
	{
		lst->buffer = malloc(sizeof(char) * BUFFER_SIZE);
		lst->cap_buffer = BUFFER_SIZE;
	}
	return (lst->buffer);
}

char *get_next_line(int fd)
{
	static t_LIST fileds[MAX_FD];
	char *newline;
	t_LIST *lst;
	int bytes;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	lst = &fileds[fd];
	lst->buffer = lst_create(lst);
	while (lst)
	{
		newline = lst_find(lst, '\n');
		if (newline != NULL)
			return (memslice(newline, lst, NULL));
		if (lst->len_buffer >= lst->cap_buffer && lst->buffer != NULL)
			if (lst_expand(lst) == -1)
				return (NULL);
		bytes = read(fd, lst->buffer + lst->len_buffer,
					 lst->cap_buffer - lst->len_buffer);
		if (bytes == 0)
			return (lastmove(lst, NULL));
		lst->len_buffer += bytes;
	}
	return (NULL);
}