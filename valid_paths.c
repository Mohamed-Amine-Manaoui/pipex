/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:06:50 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/04/29 20:23:56 by mmanaoui         ###   ########.fr       */
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
	char	**split_tst;
	int		i;

	if (cmd[1] == 'U')
	{
		write(1, "pipex: permission denied: ", 26);
		write(1, cmd, ft_strlen(cmd));
		write(1, "\n", 1);
		exit(1);
	}
	i = ft_strlen(cmd) - 1;
	while (i >= 0)
	{
		if (cmd[i] == '/')
		{
			tst = ft_substr(cmd, i + 1, ft_strlen(cmd) - 1);
			split_tst = ft_split(tst, ' ');
			return (split_tst[0]);
		}
		i--;
	}
	return (cmd);
}

char	*handle_cmds_2(char *cmd)
{
	char	*tst;
	char	**split_tst;
	int		i;

	i = ft_strlen(cmd) - 1;
	while (i >= 0)
	{
		if (cmd[i] == '/')
		{
			tst = ft_substr(cmd, i + 1, ft_strlen(cmd) - 1);
			break ;
		}
		else if (cmd[i] == '.' && cmd[i - 1] == '/')
		{
			tst = ft_substr(cmd, i, ft_strlen(cmd) - 1);
			break ;
		}
		i--;
	}
	return (tst);
}

int	valid_path(const char *cmd1, char **env)
{
	char	*path;
	char	**path_split;
	char	**cmd_split;
	char	**cmd12;
	char	*join;
	char	*cmd2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd2 = (char *)cmd1;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 1)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			path_split = ft_split(path, ':');
			while (path_split[j])
			{
				if (cmd2[0] == '/')
				{
					cmd_split = ft_split((char *)cmd1, ' ');
					if (access(cmd_split[0], F_OK) == 0)
					{
						// printf("1\n");
						return (0);
					}
					else
					{
						printf("2\n");
						// printf("cmd1: %s\n", cmd1);
						cmd1 = handle_cmds((char *)cmd1);
						cmd_split = ft_split((char *)cmd1, ' ');
						join = ft_strjoin(path_split[j], "/");
						join = ft_strjoin(join, cmd_split[0]);
						// printf("join: %s\n", join);
						if (access(cmd1, F_OK) == 0)
						{
							return (0); // Success
						}
					}
				}
				else if (cmd1[0] == '.' && cmd1[1] == '/')
				{
					if (access(cmd1, F_OK) == 0)
						return (0);
				}
				else
				{
					// printf("3\n");
					cmd_split = ft_split((char *)cmd1, ' ');
					join = ft_strjoin(path_split[j], "/");
					join = ft_strjoin(join, cmd_split[0]);
					if (access(join, F_OK) == 0)
					{
						return (0); // Success
					}
				}
				j++;
			}
		}
		i++;
	}
	return (1); // Failure
}
