/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:40:58 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/04/29 20:46:55 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			return (path);
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
					// dprintf(2, "salam\n");
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
		i++;
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
int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	infile;
	int	outfile;
	int	pid1;
	int	pid2;

	if (ac != 5)
	{
		write(1, "Bad argument :\n", 13);
		write(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		exit(1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid1 == 0)
	{
		infile = open(av[1], O_RDONLY, 0777);
		if (infile == -1)
		{
			perror(av[1]);
			exit(1);
		}
		if (av[2][0] == '\0')
		{
			exit(0);
		}
		if (find_path(env) == NULL)
		{
			if (access(av[2], F_OK) == 0)
			{
				close(fd[0]);
				dup2(infile, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(infile);
				close(fd[1]);
				execve(search_path(av[2], env), split_cmd(av[2]), env);
				perror("execve");
				exit(1);
			}
			else
			{
				if (av[2][0] == '.' && av[2][1] == '/')
				{
					write(1, "no such file or directory: ", 27);
					write(1, av[2], ft_strlen(av[2]));
					write(1, "\n", 1);
					exit(1);
				}
				else
				{
					write(1, "command not found: ", 19);
					write(1, av[2], ft_strlen(av[2]));
					write(1, "\n", 1);
					exit(1);
				}
			}
		}
		else if (valid_path((const char *)av[2], env))
		{
			perror("path");
			exit(1);
		}
		close(fd[0]);
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(infile); // ?
		close(fd[1]);
		execve(search_path((const char *)av[2], env), split_cmd(av[2]), env);
		perror("execve");
		exit(1);
		// fonction katjbd lpath / fonction catspliti cmd
	}
	else // parent
	{
		pid2 = fork(); // child2
		if (pid2 < 0)
		{
			perror("fork");
			exit(1);
		}
		else if (pid2 == 0)
		{
			if (av[3][0] == '\0')
			{
				exit(0);
			}
			outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (outfile == -1)
			{
				perror(av[ac - 1]);
				exit(1);
			}
			if (find_path(env) == NULL)
			{
				if (access(av[3], F_OK) == 0)
				{
					close(fd[1]);
					dup2(fd[0], STDIN_FILENO);
					dup2(outfile, STDOUT_FILENO);
					close(outfile);
					close(fd[0]);
					execve(search_path(av[3], env), split_cmd(av[3]), env);
					perror("execve");
					exit(1);
				}
				else
				{
					if(av[3][0] == '.' && av[3][1] == '/')
					{
						write(1, "no such file or directory: ", 27);
						write(1, av[3], ft_strlen(av[3]));
						write(1, "\n", 1);
						exit(1);
					}
					else
					{
						write(1, "command not found: ", 19);
						write(1, av[3], ft_strlen(av[3]));
						write(1, "\n", 1);
						exit(1);
					}
				}
			}
			else if (valid_path(av[3], env))
			{
				perror("path");
				exit(1);
			}
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
			close(fd[0]);
		// printf("path: %s\n", search_path(av[3], env));
		
			execve(search_path(av[3], env), split_cmd(av[3]), env);
			perror("execve");
			exit(1);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
	return (0);
}
//  infile cmd1 cmd2 outfile
