/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:33:58 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/03/31 03:04:58 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_malloc
{
	void			*data;
	struct s_malloc	*next;
}					t_malloc;

void	*ft_malloc(size_t size, char f_or_m);
#endif