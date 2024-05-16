/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:06:50 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/15 19:58:39 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	help_valid_path(char *cmd1, char *path)
{
	char	*join;
	char	**cmd_split;

	cmd1 = handle_cmds(cmd1);
	cmd_split = ft_split(cmd1, " \n\t\v\f\r");
	join = ft_strjoin(path, "/");
	join = ft_strjoin(join, cmd_split[0]);
}

char	*ft_help(char *cmd1, char **path_split, int j)
{
	char	*join;
	char	**cmd_split;

	cmd_split = ft_split(handle_cmds((char *)cmd1), " \n\t\v\f\r");
	join = ft_strjoin(path_split[j], "/");
	join = ft_strjoin(ft_strjoin(path_split[j], "/"), cmd_split[0]);
	return (join);
}

int	hamza(char *cmd1, char **path_split, int j)
{
	char	*join;

	if (cmd1[0] == '.' && cmd1[1] == '/')
	{
		if (access(cmd1, F_OK) == 0)
			return (0);
	}
	else
	{
		join = help_path2(path_split[j], cmd1);
		if (access(join, F_OK) == 0)
			return (0);
	}
	return (1);
}

int	l7ssn(char *cmd1, char **path_split, int j, char *cmd2)
{
	char	**cmd_split;

	while (path_split[++j])
	{
		if (cmd2[0] == '/')
		{
			cmd_split = ft_split((char *)cmd1, " \n\t\v\f\r");
			if (access(cmd_split[0], F_OK) == 0)
				return (0);
			else
			{
				ft_help((char *)cmd1, path_split, j);
				if (access(handle_cmds((char *)cmd1), F_OK) == 0)
					return (0);
			}
		}
		else if (hamza((char *)cmd1, path_split, j) == 0)
		{
			return (0);
		}
	}
	return (1);
}

int	valid_path(const char *cmd1, char **env)
{
	char	*path;
	char	**path_split;
	char	*cmd2;
	int		i;
	int		j;

	i = 0;
	j = -1;
	cmd2 = (char *)cmd1;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 1)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			path_split = ft_split(path, ":");
			if (l7ssn((char *)cmd1, path_split, j, cmd2) == 0)
				return (0);
		}
		else if (access(cmd1, F_OK) == 0)
			return (0);
		i++;
	}
	return (1);
}
