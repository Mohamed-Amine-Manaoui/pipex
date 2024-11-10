/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:23:06 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:05:51 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*help_path(char *path_split, const char *cmd1)
{
	char	*join;

	cmd1 = handle_cmds((char *)cmd1);
	join = ft_strjoin(path_split, "/");
	join = ft_strjoin(join, (char *)cmd1);
	return (join);
}

char	*help_path2(char *path_split, const char *cmd1)
{
	char	*join;
	char	**cmd_split;

	cmd_split = ft_split((char *)cmd1, " \n\t\v\f\r");
	join = ft_strjoin(path_split, "/");
	join = ft_strjoin(join, cmd_split[0]);
	return (join);
}

char	*else_true_path(const char *cmd1, char **env, int i)
{
	char	*join;

	if (ft_strncmp(env[i], "PATH=", 5) == 0)
	{
		cmd1 = handle_cmds((char *)cmd1);
		join = ft_strjoin("/", (char *)cmd1);
		if (access(join, F_OK) == 0)
			return (join);
	}
	else
	{
		if (cmd1[0] == '/' || (cmd1[0] == '.' && cmd1[1] == '/'))
		{
			write(2, (char *)cmd1, ft_strlen((char *)cmd1));
			write(2, ": no such file or directory\n", 28);
			(ft_malloc (0, 'f'), exit(127));
		}
		else
		{
			write(2, (char *)cmd1, ft_strlen((char *)cmd1));
			write(2, ": command not found\n", 20);
			(ft_malloc (0, 'f'), exit(127));
		}
	}
	return (NULL);
}

char	*true_path(const char *cmd1, char **path_split, char **env, int i)
{
	char	*join;
	int		j;

	j = -1;
	while (path_split[++j])
	{
		if (cmd1[0] == '/')
		{
			join = help_path(path_split[j], cmd1);
			if (access(join, F_OK) == 0)
				return (join);
		}
		else if (cmd1[0] == '.' && cmd1[1] == '/')
		{
			if (access(cmd1, F_OK) == 0)
				return ((char *)cmd1);
		}
		else
		{
			join = help_path2(path_split[j], cmd1);
			if (access(join, F_OK) == 0)
				return (join);
		}
	}
	return (else_true_path(cmd1, env, i));
}

char	*for_path(const char *cmd1, char **env, char **path_split)
{
	char	*path;
	int		i;
	int		k;

	k = 0;
	i = 0;
	path = NULL;
	while (env[k])
	{
		while (ft_strncmp(env[i], "PATH=", 5) != 1)
			i++;
		if (ft_strncmp(env[i], "PATH=", 5) == 1)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			path_split = ft_split(path, ":");
			return (true_path(cmd1, path_split, env, i));
		}
		k++;
	}
	return (NULL);
}
