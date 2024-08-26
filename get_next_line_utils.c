/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshpilev <vshpilev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:47:47 by vshpilev          #+#    #+#             */
/*   Updated: 2024/08/19 16:47:49 by vshpilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	if (c == 0)
	{
		i = ft_strlen((char *)s);
		return (&s[i]);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *stash, char *buf)
{
	char	*res;
	int		i;
	int		j;
	size_t	len;

	if (!stash && !buf)
		return (NULL);
	len = ft_strlen(stash) + ft_strlen(buf);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (stash && stash[i] != 0)
	{
		res[i] = stash[i];
		i++;
	}
	j = 0;
	while (buf && buf[j] != 0)
		res[i++] = buf[j++];
	res[len] = '\0';
	return (res);
}

size_t	nl_index(char *start)
{
	size_t	i;

	if (!start)
		return (0);
	i = 0;
	while (start[i] != '\0' && start[i] != '\n')
		i++;
	if (start[i] == '\n')
		i++;
	return (i);
}
