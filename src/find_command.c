/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:29:46 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/04 02:19:57 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exec_command(t_arg *arg, int sig)
{
	pid_t		pid;
	
	pid = fork();
	if (sig == 1)
		execve("./bin/exe_echo", arg->argv, environ);
	waitpid(pid, NULL, 0);
}

void			find_command(t_arg *arg)
{
	if (!ft_strcmp(arg->argv[0], "echo"))
		exec_command(arg, 1);
//	else if (!ft_strcmp(arg->argv[0], "env"))
//		exec_env();
//	else if (!ft_strcmp(arg->argv[0], "cd"))
//		exec_cd();
//	else if (!ft_strcmp(arg->argv[0], "setenv"))
//		exec_setenv();
//	else if (!ft_strcmp(arg->argv[0], "unsetenv"))
//		exec_unsetenv();
//	else if (!ft_strcmp(arg->argv[0], "exit"))
//		exec_exit();
	else
	{
		write(1, "minishell: command not found: ", 30);
		write(1, arg->argv[0], ft_strlen(arg->argv[0]));
		write(1, "\n", 1);
	}
}
