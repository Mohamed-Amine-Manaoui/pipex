/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:33:52 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:08:39 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*handle_cmds(char *cmd)
{
	char	*tst;
	char	**split_tst;
	int		i;

	if (cmd[1] == 'U')
	{
		write(2, "pipex: permission denied: ", 26);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		(ft_malloc (0, 'f'), exit(1));
	}
	i = ft_strlen(cmd) - 1;
	while (i >= 0)
	{
		if (cmd[i] == '/')
		{
			tst = ft_substr(cmd, i + 1, ft_strlen(cmd) - 1);
			split_tst = ft_split(tst, " \n\t\v\f\r");
			return (split_tst[0]);
		}
		i--;
	}
	return (cmd);
}

char	*handle_cmds_2(char *cmd)
{
	char	*tst;
	int		i;

	tst = NULL;
	i = ft_strlen(cmd) - 1;
	while (i >= 0)
	{
		if (cmd[i] == '/')
		{
			tst = ft_substr(cmd, i + 1, ft_strlen(cmd) - 1);
			break ;
		}
		else if (cmd[i] == '.' && cmd[i - 1] == '/')
		{
			tst = ft_substr(cmd, i, ft_strlen(cmd) - 1);
			break ;
		}
		else
		{
			tst = ft_strdup(cmd);
			break ;
		}
		i--;
	}
	return (tst);
}
