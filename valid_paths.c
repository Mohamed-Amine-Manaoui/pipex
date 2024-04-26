/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:06:50 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/04/26 08:45:14 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	length1;
	size_t	length2;
	size_t	i;
	size_t	j;

	length2 = ft_strlen(s2);
	length1 = ft_strlen(s1);
	ptr = malloc(length1 + length2 + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}
char	*handle_cmds(char *cmd)
{
	char	*tst;
	int		i;

	i = ft_strlen(cmd) - 1;
	while (i >= 0)
	{
		if (cmd[i] == '/')
		{
			tst = ft_substr(cmd, i + 1, ft_strlen(cmd) - 1);
			break ;
		}
		i--;
	}
	return (tst);
}

int	valid_path(char *cmd1, char **env)
{
	char	*path;
	char	**path_split;
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 1)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			path_split = ft_split(path, ':');
			while (path_split[j])
			{
				if (cmd1[0] == '/')
				{
					cmd1 = handle_cmds(cmd1);
				}
				join = ft_strjoin(path_split[j], "/");
				join = ft_strjoin(join, cmd1);
				if (access(join, F_OK) == 0)
				{
					return (0); // Success
				}
				j++;
			}
		}
		i++;
	}
	return (1); // Failure
}
