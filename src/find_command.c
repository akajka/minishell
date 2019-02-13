/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:29:46 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/13 04:01:53 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*create_path(char *tmp)
{
	int			i;
	int			adr;
	char		*buf;
	char		*temp;

	i = -1;
	while (tmp && (adr = ft_strchr_int(tmp, ':')))
	{
		buf = ft_strsub(tmp, 0, (adr ? adr : ft_strlen(tmp)));
		temp = ft_strjoin(buf, "/");
		free(buf);
		buf = ft_strjoin(temp, g_arg->argv[0]);
		free(temp);
		if (!access(buf, 0))
			return (buf);
		tmp += adr + 1;
		free(buf);
	}
	return (NULL);
}

void			child_process(char *tmp)
{
	int			i;
	t_stat		stat;
	char		*path;

	i =  0;
	path = ((!tmp || ft_strchr(g_arg->argv[0], '/')) ?
			g_arg->argv[0] : create_path(tmp));
	if (lstat(path, &stat) & S_IRUSR)
		write(2, "minishell: permission denied: ", 30);
	else
	{
		execve(path, g_arg->argv, g_arg->env);
		write(2, "minishell: command not found: ", 30);
	}
	write(2, g_arg->argv[0], ft_strlen(g_arg->argv[0]));
	write(2, "\n", 1);
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
