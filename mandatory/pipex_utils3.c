/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:06:08 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/05/15 18:45:49 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/// @brief This function is used to validate number of arguments
void	valid_argument(t_help *help, int ac)
{
	help->infile = 0;
	help->outfile = 0;
	help->split_tst = NULL;
	help->status = 0;
	if (ac != 5)
	{
		write(2, "Bad argument :\n", 13);
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		exit(1);
	}
}

/// @brief This function is used to check the pipe
void	check_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

/// @brief This function is used to check the pid
void	check_pid(int pid)
{
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
}
