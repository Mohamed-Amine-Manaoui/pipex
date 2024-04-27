/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:40:58 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/04/27 06:44:36 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*search_path(char *cmd1, char **env)
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
					return (join);
				}
				j++;
			}
		}
		i++;
	}
	return ("path not found"); // Failure
}

char	**split_cmd(char *cmd)
{
	return (ft_split(handle_cmds(cmd), ' '));
}

int	main(int ac, char **av, char **env)
{
	int	pid;
	int	fd[2];
	int	infile;
	int	outfile;
	int	pid_1;
	int	pid_2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid_1 = fork();
	pid_2 = fork();
	if (pid_1 == 0)
	{
		infile = open(av[1], O_RDONLY, 0777);
		if (infile == -1)
		{
			perror("file");
			exit(1);
		}
		if (valid_path(av[2], env))
		{
			perror("path");
			exit(1);
		}
		close(fd[0]);
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(infile); // ?
		close(fd[1]);
		execve(search_path(av[2], env), split_cmd(av[2]), env);
		perror("execve");
		exit(1);
		// fonction katjbd lpath / fonction catspliti cmd
	}
	if (pid_2 == 0)
	{
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (valid_path(av[3], env))
		{
			perror("path");
			exit(1);
		}
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(fd[1]);
		close(outfile);
		close(fd[0]);
		execve(search_path(av[3], env), split_cmd(av[3]), env);
		perror("execve");
	}
	return (0);
}
//  infile cmd1 cmd2 outfile
