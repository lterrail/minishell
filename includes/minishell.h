/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:25:07 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/29 13:55:27 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <dirent.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>

# define E_SUCCESS 1
# define E_ERROR 0

typedef void	(*t_sighandler)(int);

typedef struct		s_ms
{
	char			**env;
	char			**paths;
	char			**argcs;
	int				len_env;
	char			*first_argc;
	char			**options;
	char			*prompt;
	char			*pwd;
	char			*old_pwd;
	int				first_call;
}					t_ms;

int					ft_parser(t_ms *ms, char *line);
int					ft_find_and_copy_paths(t_ms *ms, char **env);
void				ft_exit(t_ms *ms, char *str, char *msg);
int					ft_unsetenv(t_ms *ms, char *line);
void				ft_print_env(t_ms *ms);
int					ft_setenv(t_ms *ms, char *line, int flag);
void				ft_free_tab(char **tab, int len);
void				ft_exec_cmd(t_ms *ms, char *path, char *line);
void				ft_exec_cmd_with_path(t_ms *ms, char *path, char *line);
void				ft_init_cd(t_ms *ms, char *line);
void				ft_exec_cd(t_ms *ms, int flag, char *argcs);
char				*ft_get_last_argc(char *str);
int					ft_find_env_variable(t_ms *ms, char *var);
void				ft_free_cd(t_ms *ms);
char				*ft_search_valid_builtin(t_ms *ms);
void				ft_print_paths(t_ms *ms);
void				ft_get_first_argc(t_ms *ms, char *line);
char				*ft_check_line(char *line, int len);
void				ft_env_i(t_ms *ms, char *line);
void				ft_chdir_back(t_ms *ms, char *line);
void				ft_chdir(t_ms *ms, char *line);
void				ft_signal_handler(int sig);

#endif
