/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:29:46 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/15 12:21:09 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				create_path(char *path, char *tmp, char c)
{
	int			i;

	i = 0;
	if (!ft_strchr(tmp, c))
		return (0);
	while (*(tmp + i) && *(tmp + i) != c)
	{
		path[i] = *(tmp + i);
		i++;
	}
	path[i] = '/';
	path[i + 1] = '\0';
	return (i);
}

char			*get_dir(char *path)
{
	char		*dir;
	int			len;

	if (!path)
		return (NULL);
	len = ft_strrchr_int(path, '/');
	dir = ft_strsub(path, 0, len);
	return (dir);
}

void			child_process(char *tmp)
{
	int			i;
	int			perm_test;
	char		path[1024];

	perm_test = 0;
	ft_strclr(path);
	i = create_path(path, g_arg->argv[0], '/');
	while (path[0] != '\0' || !i)
	{
		if (!access(path, R_OK))
			perm_test = !(perm_test);
		ft_strcat(path, g_arg->argv[0]);
		execve(path, g_arg->argv, g_arg->env);
		if (!tmp)
			break ;
		tmp += i;
		if (*(tmp += 1) == '\0')
			break ;
		ft_strclr(path);
		i = create_path(path, tmp, ':');
	}
	if (!perm_test && tmp)
		write(2, "minishell: permission denied: ", 30);
	else
		write(2, "minishell: command not found: ", 30);
	ft_putendl_fd(g_arg->argv[0], 2);
	exit(1);
}

void			system_builtins(void)
{
	pid_t		pid;
	char		*tmp;

	tmp = get_env("PATH=");
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
