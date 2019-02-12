/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:32:02 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/13 00:52:22 by akorobov         ###   ########.fr       */
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
# include <term.h>
# include "../libft/libft.h"

typedef struct	s_arg
{
	char		*welcome_str;
	char		**env;
	char		oldpwd[1024];
	int			sig;
	int			argc;
	char		**argv;
	char		buf[1024];
}				t_arg;

t_arg			*g_arg;
void			env_cpy();
void			clean_arg();
void			loop();
void			welcome();
void			getargv();
int				env_finder(char *env, int len);
char			*get_env(char *env);
void			hendle_arg();
void			find_command();
void			system_builtins();
void			exec_echo();
void			exec_history();
void			exec_env();
void			exec_setenv(char *env);
void			exec_unsetenv(char *env);
void			exec_cd();
void			exec_pwd();
void			exec_exit();
void			sig_handl(int sig);

#endif
