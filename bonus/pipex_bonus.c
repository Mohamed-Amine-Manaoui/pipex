/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:55:52 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:10:10 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	multiple_pipe(int ac, char **av, char **env, t_help *help)
{
	help->i = 0;
	while (help->i < ac - 3)
	{
		help->pid[help->i] = fork();
		check_pid(help->pid[help->i]);
		if (help->pid[help->i] == 0)
		{
			if (help->i == 0)
				child_first_bonus(ac, av, env, help);
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

void	allocate_memory_bonus(int ac, t_help *help)
{
	int	i;

	help->fds = ft_malloc(sizeof(int *) * ac - 4, 'm');
	if (help->fds == NULL)
		return ;
	i = 0;
	while (i < ac - 4)
	{
		help->fds[i] = ft_malloc(sizeof(int) * 2, 'm');
		if (help->fds[i] == NULL)
			return ;
		i++;
	}
	help->pid = ft_malloc(sizeof(int) * ac - 3, 'm');
	if (help->pid == NULL)
		return ;
}

/// @brief Bonus
int	main(int ac, char **av, char **env)
{
	t_help	help;

	allocate_memory_bonus(ac, &help);
	valid_argument_bonus(ac, av, &help);
	pipe_fds(&help, ac);
	if (ft_strncmp(av[1], "here_doc", 8))
	{
		_here_doc(ac, av, env, &help);
	}
	else
	{
		multiple_pipe(ac, av, env, &help);
	}
	return ((help.status >> 8) & 0xff);
}
