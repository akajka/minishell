/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:29:46 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/12 23:36:41 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				create_path(char *path, char *tmp)
{
	int			i;

	i = 0;
	while (*(tmp + i) && *(tmp + i) != ':')
	{
		path[i] = *(tmp + i);
		i++;
	}
	path[i] = '/';
	ft_strcat(path, g_arg->argv[0]);
	return (i);
}

void			child_process(char *tmp)
{
	int			i;
	char		path[1024];

	i =  0;
	ft_strcpy(path, g_arg->argv[0]);
	while (path[0] != '\0')
	{
		execve(path, g_arg->argv, g_arg->env);
		if (!tmp)
			break ;
		tmp += i;
		if (*(tmp += 1) == '\0')
			break ;
		ft_strclr(path);
		i = create_path(path, tmp);
	}
	write(2, "minishell: command not found: ", 30);
	write(2, g_arg->argv[0], ft_strlen(g_arg->argv[0]));
	write(2, "\n", 1);
	exit(1);
}

void			system_builtins(void)
{
	int			i;
	pid_t		pid;
	char		*tmp;

	i = -1;
	while (g_arg->env[++i] && ft_strncmp(g_arg->env[i], "PATH=", 5))
		continue ;
	if (g_arg->env[i])
		tmp = ft_strchr(*(g_arg->env + i), '=') + 1;
	else
		tmp = NULL;
	pid = fork();
	if (pid == 0)
		child_process(tmp);
	else
		waitpid(pid, NULL, 0);
}

void			find_command(void)
{
	if (!ft_strcmp(g_arg->argv[0], "echo"))
		exec_echo();
	else if (!ft_strcmp(g_arg->argv[0], "env"))
		exec_env();
	else if (!ft_strcmp(g_arg->argv[0], "setenv"))
		exec_setenv(g_arg->argv[1]);
	else if (!ft_strcmp(g_arg->argv[0], "unsetenv"))
		exec_unsetenv(g_arg->argv[1]);
	else if (!ft_strcmp(g_arg->argv[0], "cd"))
		exec_cd();
	else if (!ft_strcmp(g_arg->argv[0], "pwd"))
		exec_pwd();
	else if (!ft_strcmp(g_arg->argv[0], "exit"))
		exit(EXIT_SUCCESS);
	else
		system_builtins();
}
