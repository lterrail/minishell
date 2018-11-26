/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:25:07 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/26 20:12:26 by lterrail         ###   ########.fr       */
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
# define DELETE -1
# define HOME -2
# define TILD -3
# define ADD -4
# define MOINS -5
# define SLASH -6

typedef struct		s_ms
{
	char			**env;
	char			**paths;
	int				len_env;
	char			*first_argc;
	char			**options;
	char			*prompt;
	char			*pwd;
	char			*old_pwd;
	int				error;
	int				first_call;
}					t_ms;

int					ft_parse_cmd(t_ms *ms, char *line);
int					ft_find_and_copy_paths(t_ms *ms, char **env);
void				ft_exit(t_ms *ms, char *str, char *msg);
int					ft_unsetenv(t_ms *ms, char *line);
void				ft_print_env(t_ms *ms);
int					ft_setenv(t_ms *ms, char *line);
void				ft_free_tab(char **tab, int len);
void				ft_exec_cmd(t_ms *ms, char *path, char *line);
void				ft_exec_cmd_with_path(t_ms *ms, char *path, char *line);
void				ft_init_cd(t_ms *ms, char *line);
void				ft_exec_cd(t_ms *ms, int flag, char *argcs);
char				*ft_get_last_argc(char *str);
int					ft_find_env_variable(t_ms *ms, char *var);
char				*ft_add_new_argc(t_ms *ms, char *add, int i, char *cwd);
void				ft_swap_argcs(t_ms *ms);
void				ft_add_argc(t_ms *ms, char *argcs);
void				ft_del_last_argc(t_ms *ms);
void				ft_get_home(t_ms *ms);

#endif
