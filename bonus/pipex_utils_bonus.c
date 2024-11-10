/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:12:19 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:08:39 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	valid_argument_bonus(int ac, char **av, t_help *help)
{
	help->outfile = 0;
	help->i = 0;
	if (ac < 5)
	{
		write(2, "Bad argument :\n", 13);
		write(2, "Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 45);
		(ft_malloc (0, 'f'), exit(1));
	}
	if (av[2][0] == '\0')
	{
		write(2, "syntax error near unexpected token |\n", 37);
		(ft_malloc (0, 'f'), exit(1));
	}
}

void	pipe_fds(t_help *help, int ac)
{
	int	i;

	i = 0;
	while (i < ac - 4)
	{
		if (pipe(help->fds[i]) == -1)
		{
			perror("pipe");
			(ft_malloc (0, 'f'), exit(1));
		}
		i++;
	}
}

void	ft_close(int **fds, int ac)
{
	int	j;

	j = 0;
	while (j < ac - 4)
	{
		close(fds[j][0]);
		close(fds[j][1]);
		j++;
	}
}
