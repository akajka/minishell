/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:32:02 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/06 15:31:56 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

extern char		**environ;

typedef struct	s_arg
{
	t_list		*history;
	t_list		*cd;
	int			sig;
	int			argc;
	char		**argv;
	char		buf[1024];
}				t_arg;

void			loop(t_arg *arg, int *count, char c);
void			parse_buf(t_arg *arg, int i);
void			findchar(t_arg *arg, char c, int *count);
void			getargv(t_arg *arg);
void			hendle_arg(t_arg *arg);
void			find_command(t_arg *arg);
void			system_builtins(t_arg *arg);
void			exec_echo(t_arg *arg);
void			exec_history(t_arg *arg);
void			exec_env(t_arg *arg);
void			exec_setenv(t_arg *arg);
void			exec_unsetenv(t_arg *arg);
void			exec_cd(t_arg *arg);
void			exec_pwd(t_arg *arg);
void			exec_exit(t_arg *arg);

#endif
