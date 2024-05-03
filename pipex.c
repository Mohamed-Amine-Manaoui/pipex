/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:40:58 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/03 17:21:52 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		infile;
	int		outfile;
	int		pid1;
	int		pid2;
	char	**split_tst;
	int		status;

	status = 0;
	if (ac != 5)
	{
		write(2, "Bad argument :\n", 13);
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
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
			exit(0);

		if (find_path(env) == NULL)
		{
			split_tst = ft_split(av[2], ' ');
			if (access(split_tst[0], F_OK) == 0)
			{
				close(fd[0]);
				dup2(infile, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(infile);
				close(fd[1]);
				execve(search_path(split_tst[0], env), split_cmd(av[2]), env);
				perror("execve111111");
				exit(1);
			}
			else
			{
				if (av[2][0] == '.' && av[2][1] == '/')
				{
					write(2, "no such file or directory: ", 27);
					write(2, av[2], ft_strlen(av[2]));
					write(2, "\n", 1);
					exit(127);
				}
				else
				{
					write(2, "command not found: ", 19);
					write(2, av[2], ft_strlen(av[2]));
					write(2, "\n", 1);
					exit(127);
				}
			}
		}
		else if (valid_path((const char *)av[2], env))
		{
			if (av[2][0] == '/' || av[2][0] == '.')
				{
					dprintf(2, "pipex: %s: No such file or directory\n", av[2]);
				}
				else
				{
					dprintf(2, "pipex: %s: command not found\n", av[2]);
				}
			exit(1);
		}
		close(fd[0]);
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(infile); // ?
		close(fd[1]);
		execve(search_path((const char *)av[2], env), split_cmd(av[2]), env);
		// dprintf(2, "command not found: \n");
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
				split_tst = ft_split(av[3], ' ');
				if (access(split_tst[0], F_OK) == 0)
				{
					close(fd[1]);
					dup2(fd[0], STDIN_FILENO);
					dup2(outfile, STDOUT_FILENO);
					close(outfile);
					close(fd[0]);
					execve(search_path(split_tst[0], env), split_cmd(av[3]), env);
					// dprintf(2, "command not found: %s\n", av[3]);
					exit(127);
				}
				else
				{
					if (av[3][0] == '.' && av[3][1] == '/')
					{
						write(2, "no such file or directory: ", 27);
						write(2, av[3], ft_strlen(av[3]));
						write(2, "\n", 1);
						exit(1);
					}
					else
					{
						write(2, "command not found: ", 19);
						write(2, av[3], ft_strlen(av[3]));
						write(2, "\n", 1);
						exit(127);
					}
				}
			}
			else if (valid_path((const char *)av[3], env) == 1)
			{
				if (av[3][0] == '/' || av[3][0] == '.')
				{
					dprintf(2, "pipex: %s: No such file or directory\n", av[3]);
				}
				else
				{
					dprintf(2, "pipex: %s: command not found\n", av[3]);
				}
				exit(127);
			}
			
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
			close(fd[0]);
			execve(search_path(av[3], env), split_cmd(av[3]), env);
			// write(2, "command not found: ", 19);
			exit(1);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid1, &status, 0);
			waitpid(pid2, &status, 0);
		}
	}
	return ((status >> 8) & 0xff);
}
//  infile cmd1 cmd2 outfile
