/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:25:07 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/24 12:46:19 by lterrail         ###   ########.fr       */
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

typedef struct		s_ms
{
	char			**env;
	char			**paths;
	int				len_env;
	char			*pwd;
	char			*first_argc;
	char			**options;
}					t_ms;

int					ft_search_cmd_in_paths(t_ms *ms, char *line);
int					ft_parse_cmd(t_ms *ms, char *line);
int					ft_find_and_copy_paths(t_ms *ms, char **env);
void				ft_exit(t_ms *ms, char *str, char *msg);
int					ft_unsetenv(t_ms *ms, char *line);
void				ft_print_env(t_ms *ms);
int					ft_setenv(t_ms *ms, char *line);
void				ft_free_tab(char **tab, int len);
int					ft_init_exec_cmd(t_ms *ms, char *cmd, char *line, int flag);

#endif
