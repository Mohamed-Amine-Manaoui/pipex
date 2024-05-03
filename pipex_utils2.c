/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:56:24 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/03 15:37:37 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

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
			if(ft_strlen(path) > 5)
			{
				return (path);
			}
			else
			{
				return (NULL);
			}
		}
		i++;
	}
	return (NULL);
}

char	*search_path(const char *cmd1, char **env)
{
	char	*path;
	char	**path_split;
	char	*join;
	char	**cmd_split;
	char	*cmd2;
	int		i;
	int		j;

	cmd2 = (char *)cmd1;
	i = 0;
	j = 0;
	// exit(1);
	if(find_path(env) == NULL)
	{
			return ((char *)cmd1);
	}
	else {
	while (env[i])
	{
		while (ft_strncmp(env[i], "PATH=", 5) != 1)
			i++;
		if (ft_strncmp(env[i], "PATH=", 5) == 1)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			path_split = ft_split(path, ':');
			while (path_split[j])
			{
				if (cmd2[0] == '/')
				{
					cmd1 = handle_cmds((char *)cmd1);
					join = ft_strjoin(path_split[j], "/");
					join = ft_strjoin(join, (char *)cmd1);
					if (access(join, F_OK) == 0)
					{
						return (join);
					}
				}
				else if (cmd1[0] == '.' && cmd1[1] == '/')
				{
					if (access(cmd1, F_OK) == 0)
						return ((char *)cmd1);
				}
				else
				{
					cmd_split = ft_split((char *)cmd1, ' ');
					join = ft_strjoin(path_split[j], "/");
					join = ft_strjoin(join, cmd_split[0]);
					if (access(join, F_OK) == 0)
					{
						return (join);
					}
				}
				j++;
			}
		}
		}
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			cmd1 = handle_cmds((char *)cmd1);
			join = ft_strjoin("/", (char *)cmd1);
			if (access(join, F_OK) == 0)
				return (join);
		}
		// this condition is for the case when the path is not found
		
	}
	return (NULL); // Failure
	}

char	**split_cmd(char *cmd)
{
	char	**cmd_split;
	char	*cmd2;

	cmd2 = handle_cmds_2(cmd);
	cmd_split = ft_split(cmd2, ' ');
	return (cmd_split);
}