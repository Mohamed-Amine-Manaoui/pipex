/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_second_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:09:18 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:08:39 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	duplicate_for_ch2_b(int ac, t_help *help)
{
	dup2(help->fds[help->i - 1][0], STDIN_FILENO);
	dup2(help->outfile, STDOUT_FILENO);
	close(help->outfile);
	ft_close(help->fds, ac);
}

void	path_not_valid_ch2_b(char **av, int ac)
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
	(ft_malloc (0, 'f'), exit(127));
}

void	path_null_ch2_b(char **av, char **env, t_help *help, int ac)
{
	help->split_tst = ft_split(av[ac - 2], " \n\t\v\f\r");
	if (access(help->split_tst[0], F_OK) == 0)
	{
		duplicate_for_ch2_b(ac, help);
		execve(search_path(help->split_tst[0], env), split_cmd(av[2]), env);
		perror("execve");
		(ft_malloc (0, 'f'), exit(1));
	}
	else
	{
		if (av[2][0] == '.' && av[2][1] == '/')
		{
			write(2, "no such file or directory: ", 27);
			write(2, av[2], ft_strlen(av[2]));
			write(2, "\n", 1);
			(ft_malloc (0, 'f'), exit(127));
		}
		else
		{
			write(2, "command not found: ", 19);
			write(2, av[2], ft_strlen(av[2]));
			write(2, "\n", 1);
			(ft_malloc (0, 'f'), exit(127));
		}
	}
}

void	child_second_bonus(int ac, char **av, char **env, t_help *help)
{
	if (av[ac - 2][0] == '\0')
		exit(0);
	help->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (help->outfile == -1)
	{
		perror(av[ac - 1]);
		(ft_malloc (0, 'f'), exit(1));
	}
	if (find_path(env) == NULL)
	{
		path_null_ch2_b(av, env, help, ac);
	}
	else if (valid_path((const char *)av[ac - 2], env))
	{
		path_not_valid_ch2_b(av, ac);
	}
	duplicate_for_ch2_b(ac, help);
	execve(search_path(av[ac - 2], env), split_cmd(av[ac - 2]), env);
	perror("execve111");
	(ft_malloc (0, 'f'), exit(1));
}
