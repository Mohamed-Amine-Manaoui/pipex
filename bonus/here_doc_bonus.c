/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:49:56 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/16 22:40:09 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	path_null_ch1_here_b(char **av, char **env, t_help *help, int ac)
{
	help->split_tst = ft_split(av[3], " \n\t\v\f\r");
	if (access(help->split_tst[0], F_OK) == 0)
	{
		duplicate_for_ch1_b(ac, help);
		execve(search_path(help->split_tst[0], env), split_cmd(av[3]), env);
		perror("execve");
		exit(1);
	}
	else
	{
		if (av[3][0] == '.' && av[3][1] == '/')
		{
			write(2, "no such file or directory: ", 27);
			write(2, av[3], ft_strlen(av[3]));
			write(2, "\n", 1);
			exit(127);
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

void	child_first_here_bonus(int ac, char **av, char **env, t_help *help)
{
	if (av[3][0] == '\0')
		exit(1);
	if (find_path(env) == NULL)
	{
		path_null_ch1_here_b(av, env, help, ac);
	}
	else if (valid_path((const char *)av[3], env))
	{
		path_not_valid_ch1_b(av);
	}
	duplicate_for_ch1_b(ac, help);
	execve(search_path((const char *)av[3], env), split_cmd(av[3]), env);
	perror("execve");
	exit(1);
}

void	multiple_pipe_here(int ac, char **av, char **env, t_help *help)
{
	help->i = 0;
	while (help->i < ac - 3)
	{
		help->pid[help->i] = fork();
		check_pid(help->pid[help->i]);
		if (help->pid[help->i] == 0)
		{
			if (help->i == 0)
				child_first_here_bonus(ac, av, env, help);
			else if (help->i == ac - 3 - 1)
				child_second_bonus(ac, av, env, help);
			else
				child_n_bonus(ac, av, env, help);
		}
		help->i++;
	}
	ft_close(help->fds, ac);
	help->i = 0;
	while (help->i < ac - 3)
	{
		waitpid(help->pid[help->i], &help->status, 0);
		help->i++;
	}
}

void	_here_doc(int ac, char **av, char **env, t_help *help)
{
	char	*line;

	if (pipe(help->fd_doc) == -1)
	{
		perror("pipe");
		exit(1);
	}
	valid_argument_bonus(ac, help);
	write(1, "> ", 2);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, av[2], ft_strlen(av[2])))
			break ;
		write(help->fd_doc[1], line, ft_strlen(line));
		write(help->fd_doc[1], "\n", 1);
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	help->infile = help->fd_doc[0];
	close(help->fd_doc[1]);
	multiple_pipe_here(ac, av, env, help);
}
