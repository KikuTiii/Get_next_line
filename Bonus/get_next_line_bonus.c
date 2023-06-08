#include "get_next_line_bonus.h"

static char	*memslice(char	*newline, t_list *lst, char *line)
{
	line = lst_getslice(lst, 0, newline - lst->buffer + 1);
	if (line == NULL)
		return (NULL);
	lst->len_b -= (newline + 1) - lst->buffer;
	ft_memmove(lst->buffer, newline + 1, lst->len_b);
	return (line);
}

static char	*lastslice(t_list *lst, char *line)
{
	if (lst->len_b > 0)
	{
		line = lst_getslice(lst, 0, lst->len_b);
		if (line == NULL)
			return (NULL);
		free(lst->buffer);
		lst->buffer = NULL;
		lst->len_b = 0;
		lst = NULL;
		return (line);
	}
	if (lst->buffer[0] == '\0')
	{
		free(lst->buffer);
		lst->buffer = NULL;
	}
	return (NULL);
}

static char	*lst_create(t_list *lst)
{
	if (lst->buffer == NULL)
	{
		lst->buffer = malloc(sizeof(char) * BUFFER_SIZE);
		lst->buffer[0] = '\0';
		lst->cap_b = BUFFER_SIZE;
	}
	return (lst->buffer);
}

char	*get_next_line(int fd)
{
	static t_list		fileds[MAX_FD];
	char				*newline;
	t_list				*lst;
	int					bytes;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	lst = &fileds[fd];
	lst->buffer = lst_create(lst);
	while (lst)
	{
		newline = lst_find(lst, '\n');
		if (newline != NULL)
			return (memslice(newline, lst, NULL));
		if ((lst->cap_b - lst->len_b < BUFFER_SIZE) && lst->buffer != NULL)
			if (lst_expand(lst) == -1)
				return (NULL);
		bytes = read(fd, lst->buffer + lst->len_b, BUFFER_SIZE);
		if (bytes == -1 || bytes == 0)
			return (lastslice(lst, NULL));
		lst->len_b += bytes;
	}
	return (NULL);
}
