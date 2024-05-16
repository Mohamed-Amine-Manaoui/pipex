/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:10:12 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/15 20:25:21 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	check_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	c_word(char *str, char *charset)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_sep(str[i], charset))
			i++;
		if (str[i] != '\0')
			w++;
		while (str[i] != '\0' && !check_sep(str[i], charset))
			i++;
	}
	return (w);
}

int	c_char(char *str, char *charset)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (str[i] != '\0' && !check_sep(str[i], charset))
	{
		c++;
		i++;
	}
	return (c);
}

char	*word(char *str, char *charset)
{
	char	*w;
	int		i;

	i = 0;
	w = ft_malloc(c_char(str, charset) + 1, 'm');
	while (str[i] != '\0' && !check_sep(str[i], charset))
	{
		w[i] = str[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

char	**ft_split(char *str, char *charset)
{
	char		**split;
	int			i;
	int			w;

	w = 0;
	i = 0;
	split = ft_malloc(sizeof(char **) * (c_word(str, charset) + 1), 'm');
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_sep(str[i], charset))
			i++;
		if (str[i] != '\0')
		{
			split[w] = word(str + i, charset);
			w++;
		}
		while (str[i] != '\0' && !check_sep(str[i], charset))
			i++;
	}
	split[w] = 0;
	return (split);
}
