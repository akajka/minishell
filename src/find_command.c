/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:29:46 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/11 20:11:29 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				create_path(char *path, char *tmp, t_arg *arg)
{
	int			i;

	i = 0;
	while (*(tmp + i) && *(tmp + i) != ':')
	{
		path[i] = *(tmp + i);
		i++;
	}
	path[i] = '/';
	ft_strcat(path, arg->argv[0]);
	return (i);
}

void			child_process(t_arg *arg, char *tmp)
{
	int			i;
	char		path[1024];

	i =  0;
	ft_strcpy(path, arg->argv[0]);
	while (path[0] != '\0')
	{
		execve(path, arg->argv, arg->env);
		tmp += i;
		if (*(tmp += 1) == '\0')
			break ;
		ft_strclr(path);
		i = create_path(path, tmp, arg);
	}
	write(2, "minishell: command not found: ", 30);
	write(2, arg->argv[0], ft_strlen(arg->argv[0]));
	write(2, "\n", 1);
	exit(1);
}

void			system_builtins(t_arg *arg)
{
	int			i;
	pid_t		pid;
	char		*tmp;

	i = -1;
	pid = fork();
	while (arg->env[++i] && ft_strncmp(arg->env[i], "PATH=", 5))
		continue ;
	tmp = ft_strchr(*(arg->env + i), '=') + 1;
	if (pid == 0)
		child_process(arg, tmp);
	else
		waitpid(pid, NULL, 0);
}

void			find_command(t_arg *arg)
{
	if (!ft_strcmp(arg->argv[0], "echo"))
		exec_echo(arg);
	else if (!ft_strcmp(arg->argv[0], "env"))
		exec_env(arg);
	else if (!ft_strcmp(arg->argv[0], "setenv"))
		exec_setenv(arg);
	else if (!ft_strcmp(arg->argv[0], "cd"))
		exec_cd(arg);
	else if (!ft_strcmp(arg->argv[0], "pwd"))
		exec_pwd(arg);
	else if (!ft_strcmp(arg->argv[0], "unsetenv"))
		exec_unsetenv(arg);
	else if (!ft_strcmp(arg->argv[0], "clear"))
		write(1, "\e[1;1H\e[2J", 11);
	else if (!ft_strcmp(arg->argv[0], "exit"))
		exit(EXIT_SUCCESS);
	else
		system_builtins(arg);
}
