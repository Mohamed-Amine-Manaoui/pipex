/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:38:58 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/16 22:27:47 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/// @brief duplicate the files descriptors and close
/// the unused ones for the second child process
void	duplicatite_for_ch2(t_help *help)
{
	close(help->fd[1]);
	dup2(help->fd[0], STDIN_FILENO);
	dup2(help->outfile, STDOUT_FILENO);
	close(help->outfile);
	close(help->fd[0]);
}

/// @brief This function is used to handle
///  the case where the path is null
void	path_null_ch2(t_help *help, char **av, char **env, int ac)
{
	help->split_tst = ft_split(av[ac - 2], " \n\t\v\f\r");
	if (access(help->split_tst[0], F_OK) == 0)
	{
		duplicatite_for_ch2(help);
		execve(search_path(help->split_tst[0], env), split_cmd(av[ac - 2]),
			env);
		perror("execve");
		exit(127);
	}
	else
	{
		if (av[ac - 2][0] == '.' && av[ac - 2][1] == '/')
		{
			write(2, av[ac - 2], ft_strlen(av[ac - 2]));
			write(2, ": no such file or directory", 27);
			write(2, "\n", 1);
			exit(127);
		}
		else
		{
			write(2, av[ac - 2], ft_strlen(av[ac - 2]));
			write(2, ": no such file or directory\n", 28);
			exit(127);
		}
	}
}

/// @brief This function is used to handle
///  the case where the path is not valid
void	path_not_valid_ch2(char **av, int ac)
{
	if (av[ac - 2][0] == '/' || av[ac - 2][0] == '.')
	{
		write(2, av[ac - 2], ft_strlen(av[ac - 2]));
		write(2, " :no such file or directory\n", 28);
	}
	else
	{
		write(2, av[ac - 2], ft_strlen(av[ac - 2]));
		write(2, " :command not found\n", 20);
	}
	exit(127);
}

/// @brief This function is used to
/// handle the second child process (second command)
void	child_2(t_help *help, char **av, char **env, int ac)
{
	if (av[ac - 2][0] == '\0')
		exit(0);
	help->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (help->outfile == -1)
	{
		perror(av[ac - 1]);
		exit(1);
	}
	if (find_path(env) == NULL)
	{
		path_null_ch2(help, av, env, ac);
	}
	else if (valid_path((const char *)av[ac - 2], env) == 1)
	{
		path_not_valid_ch2(av, ac);
	}
	duplicatite_for_ch2(help);
	execve(search_path(av[ac - 2], env), split_cmd(av[ac - 2]), env);
	perror("execve");
	exit(1);
}
//./pipex infile cmd1 cmd2 outfile