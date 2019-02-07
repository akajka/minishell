/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:29:46 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/07 13:31:54 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			create_path(char *path, char *tmp, t_arg *arg)
{
	int		i;

	i = 0;
	while (*(tmp + i) && *(tmp + i) != ':')
	{
		path[i] = *(tmp + i);
		i++;
	}
	path[i] = '/';
	ft_strcat(path,arg->argv[0]);
	return (i);
}

void		system_builtins(t_arg *arg)
{
	int		i;
	pid_t	pid;
	char	path[1024];
	char	*tmp;

	i = -1;
	pid = fork();
	while (environ[++i] && ft_strncmp(environ[i], "PATH=", 5))
		continue ;
	tmp = *(environ + i);
	tmp = ft_strchr(tmp, '=') + 1;
	if (pid == 0)
	{
		i = 0;
		ft_strcpy(path, arg->argv[0]);
		while (path[0])
		{
			execve(path, arg->argv, environ);
			tmp += i;
			if (*(tmp += 1) == '\0')
				break ;
			ft_strclr(path);
			i = create_path(path, tmp, arg);
		}
		write(2, "minishell: command not found: ", 30);
		write(2, arg->argv[0], ft_strlen(arg->argv[0]));
		write(1, "\n", 1);
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
}

void		find_command(t_arg *arg)
{
	int		i;

	i = 0;
	if (!ft_strcmp(arg->argv[0], "echo"))
		exec_echo(arg);
//	else if (!ft_strcmp(arg->argv[0], "history") && ++i)
//		exec_history(arg);
	else if (!ft_strcmp(arg->argv[0], "env"))
		exec_env(arg);
	else if (!ft_strcmp(arg->argv[0], "setenv") && ++i)
		exec_setenv(arg);
	else if (!ft_strcmp(arg->argv[0], "cd") && ++i)
		exec_cd(arg);
	else if (!ft_strcmp(arg->argv[0], "pwd"))
		exec_pwd(arg);
	else if (!ft_strcmp(arg->argv[0], "unsetenv") && ++i)
		exec_unsetenv(arg);
	else if (!ft_strcmp(arg->argv[0], "exit"))
		exec_exit(arg);
	else if (++i)
		system_builtins(arg);
	if (!i)
		write(1, "\n", 1);
}
