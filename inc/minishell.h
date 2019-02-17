/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:32:02 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/16 19:22:28 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include "libft.h"

typedef struct stat		t_stat;

typedef struct			s_status
{
	int					bq;
	int					bq_pos;
	int					q;
	int					q_pos;
}						t_status;

typedef struct			s_arg
{
	t_status			stat;
	char				*welcome_str;
	char				**env;
	int					sig;
	char				path[1024];
	int					argc;
	char				**argv;
	char				buf[1024];
}						t_arg;

t_arg					*g_arg;
void					env_cpy(char **env);
void					create_env();
void					clean_arg();
void					loop();
void					welcome();
void					getargv();
int						getargc();
int						env_finder(char *env, int len);
char					*get_env(char *env);
void					hendle_arg();
void					find_command();
void					system_builtins();
void					exec_echo();
void					exec_history();
void					exec_env();
void					exec_setenv(char *env);
void					exec_unsetenv(char *env);
void					exec_cd();
void					exec_pwd();
void					exec_exit();
void					sig_handl(int sig);

#endif
