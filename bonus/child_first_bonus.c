/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_first_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:08:53 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/16 22:39:43 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/// @brief duplicate the files descriptors and close it
void	duplicate_for_ch1_b(int ac, t_help *help)
{
	dup2(help->infile, STDIN_FILENO);
	dup2(help->fds[help->i][1], STDOUT_FILENO);
	close(help->infile);
	ft_close(help->fds, ac);
}

/// @brief This function is used to handle the case where the path is not valid
void	path_not_valid_ch1_b(char **av)
{
	if (av[2][0] == '/' || av[2][0] == '.')
	{
		write(2, av[2], ft_strlen(av[2]));
		write(2, ": no such file or directory\n", 28);
	}
	else
	{
		write(2, av[2], ft_strlen(av[2]));
		write(2, ": command not found\n", 20);
	}
	exit(1);
}

/// @brief This function is used to handle the case where the path is null
void	path_null_ch1_b(char **av, char **env, t_help *help, int ac)
{
	help->split_tst = ft_split(av[2], " \n\t\v\f\r");
	if (access(help->split_tst[0], F_OK) == 0)
	{
		duplicate_for_ch1_b(ac, help);
		execve(search_path(help->split_tst[0], env), split_cmd(av[2]), env);
		perror("execve");
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

/// @brief This function is used to
/// handle the first child process (first command)
void	child_first_bonus(int ac, char **av, char **env, t_help *help)
{
	help->infile = open(av[1], O_RDONLY);
	if (help->infile == -1)
	{
		dprintf(2, "pipe\n");
		perror(av[1]);
		exit(1);
	}
	if (av[2][0] == '\0')
		exit(1);
	if (find_path(env) == NULL)
	{
		path_null_ch1_b(av, env, help, ac);
	}
	else if (valid_path((const char *)av[2], env))
	{
		path_not_valid_ch1_b(av);
	}
	duplicate_for_ch1_b(ac, help);
	execve(search_path((const char *)av[2], env), split_cmd(av[2]), env);
	perror("execve");
	exit(1);
}
