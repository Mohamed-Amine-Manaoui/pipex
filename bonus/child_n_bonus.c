/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_n_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:09:09 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/15 19:04:50 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	duplicate_for_chn_b(t_help *help, int ac)
{
	dup2(help->fds[help->i - 1][0], STDIN_FILENO);
	dup2(help->fds[help->i][1], STDOUT_FILENO);
	ft_close(help->fds, ac);
}

void	path_not_valid_chn_b(char **av, int i)
{
	if (av[i + 2][0] == '/' || av[i + 2][0] == '.')
	{
		write(2, av[i + 2], ft_strlen(av[i + 2]));
		write(2, " :no such file or directory\n", 28);
	}
	else
	{
		write(2, av[i + 2], ft_strlen(av[i + 2]));
		write(2, " :command not found\n", 20);
	}
	exit(127);
}

void	path_null_chn_b(char **av, char **env, int ac, t_help *help)
{
	help->split_tst = ft_split(av[help->i + 2], " \n\t\v\f\r");
	if (access(help->split_tst[0], F_OK) == 0)
	{
		duplicate_for_chn_b(help, ac);
		execve(search_path(help->split_tst[0], env), split_cmd(av[help->i + 2]),
			env);
		perror("execve");
		exit(1);
	}
	else
	{
		if (av[help->i + 2][0] == '.' && av[help->i + 2][1] == '/')
		{
			write(2, "no such file or directory: ", 27);
			write(2, av[help->i + 2], ft_strlen(av[help->i + 2]));
			write(2, "\n", 1);
			exit(127);
		}
		else
		{
			write(2, "command not found: ", 19);
			write(2, av[help->i + 2], ft_strlen(av[help->i + 2]));
			exit(127);
		}
	}
}

void	child_n_bonus(int ac, char **av, char **env, t_help *help)
{
	if (av[help->i + 2][0] == '\0')
		exit(0);
	if (find_path(env) == NULL)
	{
		path_null_chn_b(av, env, ac, help);
	}
	else if (valid_path((const char *)av[help->i + 2], env) == 1)
	{
		path_not_valid_chn_b(av, help->i);
	}
	duplicate_for_chn_b(help, ac);
	execve(search_path(av[help->i + 2], env), split_cmd(av[help->i + 2]), env);
	perror("execve2222");
	exit(1);
}
