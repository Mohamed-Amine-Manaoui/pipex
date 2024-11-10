/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:26:59 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:23:53 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	i = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[i]) && i != 0)
		i--;
	return (ft_substr((char *)s1, 0, i + 1));
}

char	*ft_lines(int fd, char *ptr)
{
	char	*buffer;
	ssize_t	n_byte;

	buffer = ft_malloc((size_t)BUFFER_SIZE + 1, 'm');
	if (!buffer)
		return (NULL);
	n_byte = 1;
	while (n_byte != 0 && !ft_strchr(ptr, '\n'))
	{
		n_byte = read(fd, buffer, BUFFER_SIZE);
		if (n_byte == -1)
			return (NULL);
		buffer[n_byte] = '\0';
		ptr = ft_strjoin(ptr, buffer);
		if (!ptr)
			return (NULL);
	}
	return (ptr);
}

char	*ft_line(char *ptr)
{
	size_t	i;
	size_t	k;
	char	*aide;

	i = 0;
	if (!ptr)
		return (NULL);
	if (ptr[0] == '\0')
		return (NULL);
	while (ptr[i] != '\n' && ptr[i])
		i++;
	if (ptr[i] == '\n')
		i++;
	aide = ft_malloc(i + 1, 'm');
	if (!aide)
		return (NULL);
	k = 0;
	i = 0;
	while (ptr[i] != '\n' && ptr[i])
		aide[k++] = ptr[i++];
	if (ptr[i] == '\n')
		aide[k++] = '\n';
	aide[k] = '\0';
	return (aide);
}

char	*ft_modulo(char *ptr)
{
	int		i;
	int		length;
	char	*tmp;

	if (!ptr)
		return (NULL);
	length = ft_strlen(ptr);
	i = 0;
	while (ptr[i] && ptr[i] != '\n')
		i++;
	if (ptr[i] == '\n')
		i++;
	else
	{
		return (NULL);
	}
	tmp = ptr;
	ptr = ft_substr(tmp, i, length);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*ptr;
	char		*tab;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 2147483647)
		return (NULL);
	ptr = ft_lines(fd, ptr);
	tab = ft_line(ptr);
	ptr = ft_modulo(ptr);
	return (tab);
}
