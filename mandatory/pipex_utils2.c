/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:56:24 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/15 20:08:25 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (i == n)
		return (1);
	return (0);
}

/// @brief This function is used to
/// check the path is valid or not
char	*find_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 1)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			if (ft_strlen(path) > 5)
				return (path);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

/// @brief This function is used to
/// search the path of the command (for execve)
char	*search_path(const char *cmd1, char **env)
{
	char	**path_split;
	char	*cmd2;

	cmd2 = (char *)cmd1;
	path_split = NULL;
	if (find_path(env) == NULL)
		return ((char *)cmd1);
	else
		return (for_path(cmd1, env, path_split));
	return (NULL);
}

char	**split_cmd(char *cmd)
{
	char	**cmd_split;
	char	*cmd2;

	cmd2 = handle_cmds_2(cmd);
	cmd_split = ft_split(cmd2, " \n\t\v\f\r");
	return (cmd_split);
}
