/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:33:58 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/04/26 21:06:51 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_malloc
{
	void			*data;
	struct s_malloc	*next;
}					t_malloc;
// typedef struct s_help
// {

// } t_help;

void				*ft_malloc(size_t size, char f_or_m);
char				**ft_split(char *s, char c);
int					ft_strncmp(char *s1, char *s2, int n);
char				*ft_substr(char *s, int start, int len);
int					ft_strlen(char *s);
int					valid_path(char *cmd1, char **env);
char	*ft_strjoin(char *s1, char *s2);
char				*handle_cmds(char *cmd);
#endif
