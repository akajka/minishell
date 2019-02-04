/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:29:46 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/04 22:28:40 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_command(t_arg *arg)
{
	if (!ft_strcmp(arg->argv[0], "echo"))
		exec_echo(arg);
	else if (!ft_strcmp(arg->argv[0], "env"))
		exec_env();
//	else if (!ft_strcmp(arg->argv[0], "setenv"))
//		exec_setenv();
	else if (!ft_strcmp(arg->argv[0], "cd"))
		exec_cd(arg);
	else if (!ft_strcmp(arg->argv[0], "pwd"))
		exec_pwd(arg);
//	else if (!ft_strcmp(arg->argv[0], "unsetenv"))
//		exec_unsetenv();
	else if (!ft_strcmp(arg->argv[0], "exit"))
		exec_exit(arg);
	else
	{
		write(2, "minishell: command not found: ", 30);
		write(2, arg->argv[0], ft_strlen(arg->argv[0]));
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}
