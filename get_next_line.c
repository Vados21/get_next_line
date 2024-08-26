/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshpilev <vshpilev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:47:30 by vshpilev          #+#    #+#             */
/*   Updated: 2024/08/19 16:47:40 by vshpilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*free_mem(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (NULL);
}

char	*first_line_mem(char *first_line)
{
	int		i;
	char	*line_mem;

	if (!first_line || !first_line[0])
		return (NULL);
	i = 0;
	while (first_line[i] && first_line[i] != '\n')
		i++;
	if (first_line[i] == '\n')
		i++;
	line_mem = (char *)malloc(1 + i * sizeof(char));
	if (!line_mem)
		return (NULL);
	i = 0;
	while (first_line[i] && first_line[i] != '\n')
	{
		line_mem[i] = first_line[i];
		i++;
	}
	if (first_line[i] == '\n')
		line_mem[i++] = '\n';
	line_mem[i] = '\0';
	return (line_mem);
}

static char	*new_line(char *first_line)
{
	char	*new_mem;
	size_t	nl;
	size_t	i;

	if (!first_line)
		return (NULL);
	if (first_line[0] == '\0')
		return (free_mem(&first_line));
	nl = nl_index(first_line);
	new_mem = (char *)malloc((ft_strlen(first_line) - nl + 1) * sizeof(char));
	if (!new_mem)
		return (free_mem(&first_line));
	i = 0;
	while (first_line[nl] != '\0')
		new_mem[i++] = first_line[nl++];
	new_mem[i] = '\0';
	if (new_mem[0] == '\0')
		free_mem(&new_mem);
	free_mem(&first_line);
	return (new_mem);
}

static int	readed_to_null(int fd, char **first_line, char **tmp)
{
	char	*temp;
	int		bytes;

	bytes = 1;
	while (!ft_strchr(*first_line, '\n') && (bytes != 0))
	{
		bytes = read(fd, *tmp, BUFFER_SIZE);
		if (bytes == -1)
			return (-1);
		(*tmp)[bytes] = '\0';
		temp = ft_strjoin(*first_line, *tmp);
		if (!temp)
			return (-1);
		free_mem(first_line);
		*first_line = temp;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*first_line;
	char			*tmp;
	char			*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (free_mem(&first_line));
	if (readed_to_null(fd, &first_line, &tmp) == -1)
	{
		free_mem(&tmp);
		return (free_mem(&first_line));
	}
	free_mem(&tmp);
	result = first_line_mem(first_line);
	if (!result)
		return (free_mem(&first_line));
	first_line = new_line(first_line);
	return (result);
}
