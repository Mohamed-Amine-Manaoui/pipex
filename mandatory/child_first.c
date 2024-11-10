/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:20:12 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:08:39 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/// @brief duplicate the files descriptors and close
/// the unused ones for the first child process
void	duplicatite_for_ch1(t_help *help)
{
	close(help->fd[0]);
	dup2(help->infile, STDIN_FILENO);
	dup2(help->fd[1], STDOUT_FILENO);
	close(help->infile);
	close(help->fd[1]);
}

/// @brief This function is used to
/// handle the case where the path is null
void	path_null_ch1(t_help *help, char **av, char **env)
{
	help->split_tst = ft_split(av[2], " \n\t\v\f\r");
	if (access(help->split_tst[0], F_OK) == 0)
	{
		duplicatite_for_ch1(help);
		execve(search_path(help->split_tst[0], env), split_cmd(av[2]), env);
		perror("execve");
		(ft_malloc (0, 'f'), exit(1));
	}
	else
	{
		if (av[2][0] == '.' && av[2][1] == '/')
		{
			write(2, av[2], ft_strlen(av[2]));
			write(2, ": no such file or directory", 27);
			write(2, "\n", 1);
			(ft_malloc (0, 'f'), exit(127));
		}
		else
		{
			write(2, av[2], ft_strlen(av[2]));
			write(2, ": no such file or directory", 27);
			write(2, "\n", 1);
			(ft_malloc (0, 'f'), exit(127));
		}
	}
}

/// @brief This function is used to handle
///  the case where the path is not valid
void	path_not_valid_ch1(char **av)
{
	if (av[2][0] == '/' || av[2][0] == '.')
	{
		write(2, av[2], ft_strlen(av[2]));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, av[2], ft_strlen(av[2]));
		write(2, ": command not found\n", 20);
	}
	(ft_malloc (0, 'f'), exit(1));
}

/// @brief This function is used to
/// handle the first child process (first command)
void	child_1(t_help *help, char **av, char **env)
{
	if (av[2][0] == '\0')
		exit(0);
	help->infile = open(av[1], O_RDONLY);
	if (help->infile == -1)
	{
		perror(av[1]);
		(ft_malloc (0, 'f'), exit(1));
	}
	if (find_path(env) == NULL)
	{
		path_null_ch1(help, av, env);
	}
	else if (valid_path((const char *)av[2], env))
	{
		path_not_valid_ch1(av);
	}
	duplicatite_for_ch1(help);
	execve(search_path((const char *)av[2], env), split_cmd(av[2]), env);
	perror("execve");
	(ft_malloc (0, 'f'), exit(1));
}
