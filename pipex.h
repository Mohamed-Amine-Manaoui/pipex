/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:33:58 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:33:32 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_malloc
{
	void			*data;
	struct s_malloc	*next;
}					t_malloc;
typedef struct s_help
{
	int				fd_doc[2];
	int				i;
	int				pid1;
	int				pid2;
	int				status;
	int				infile;
	int				outfile;
	int				fd[2];
	int				**fds;
	int				*pid;
	char			**split_tst;
}					t_help;

void				*ft_malloc(size_t size, char f_or_m);
char				**ft_split(char *str, char *charset);
int					ft_strncmp(char *s1, char *s2, int n);
int					ft_strlen(char *s);
int					valid_path(const char *cmd1, char **env);
char				*handle_cmds(char *cmd);
char				*handle_cmds_2(char *cmd);
char				*find_path(char **env);
char				*search_path(const char *cmd1, char **env);
char				**split_cmd(char *cmd);
void				child_1(t_help *help, char **av, char **env);
void				child_2(t_help *help, char **av, char **env, int ac);
void				valid_argument(t_help *help, int ac);
void				check_pipe(int *fd);
void				check_pid(int pid);
// bonus
int					ft_strcmp(char *s1, char *s2);
void				path_null_ch1_b(char **av, char **env, t_help *help,
						int ac);
void				ft_close(int **fds, int ac);
void				path_not_valid_ch1_b(char **av);
void				duplicate_for_ch1_b(int ac, t_help *help);
void				child_first_bonus(int ac, char **av, char **env,
						t_help *help);
void				path_null_ch2_b(char **av, char **env, t_help *help,
						int ac);
void				path_not_valid_ch2_b(char **av, int ac);
void				duplicate_for_ch2_b(int ac, t_help *help);
void				duplicate_for_chn_b(t_help *help, int ac);
void				path_not_valid_chn_b(char **av, int i);
void				path_null_chn_b(char **av, char **env, int ac,
						t_help *help);
void				child_second_bonus(int ac, char **av, char **env,
						t_help *help);
void				child_n_bonus(int ac, char **av, char **env, t_help *help);
void				valid_argument_bonus(int ac, char **av, t_help *help);
void				pipe_fds(t_help *help, int ac);
void				ft_close(int **fds, int ac);
/////////////// test
void				child_first_here_bonus(int ac, char **av, char **env,
						t_help *help);
void				multiple_pipe_here(int ac, char **av, char **env,
						t_help *help);
void				path_null_ch1_here_b(char **av, char **env, t_help *help,
						int ac);
void				_here_doc(int ac, char **av, char **env, t_help *help);
////////////////////////
char				*for_path(const char *cmd1, char **env, char **path_split);
char				*true_path(const char *cmd1, char **path_split, char **env,
						int i);
char				*help_path(char *path_split, const char *cmd1);
char				*help_path2(char *path_split, const char *cmd1);
#endif
