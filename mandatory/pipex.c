/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:40:58 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/15 18:45:49 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **env)
{
	t_help	help;

	valid_argument(&help, ac);
	check_pipe(help.fd);
	help.pid1 = fork();
	check_pid(help.pid1);
	if (help.pid1 == 0)
		child_1(&help, av, env);
	else
	{
		help.pid2 = fork();
		check_pid(help.pid2);
		if (help.pid2 == 0)
			child_2(&help, av, env, ac);
		else
		{
			close(help.fd[0]);
			close(help.fd[1]);
			waitpid(help.pid1, &help.status, 0);
			waitpid(help.pid2, &help.status, 0);
		}
	}
	return ((help.status >> 8) & 0xff);
}
