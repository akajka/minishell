/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:55:11 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/13 03:23:12 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			pwd_control(char *pwd)
{
	char		buf[1024];
	char		tmp[1024];

	getcwd(tmp, 1024);
	ft_strcpy(buf, pwd);
	ft_strcat(buf, tmp);
	exec_setenv(buf);
}

char			*find_path()
{
	if (g_arg->argv[1] && !ft_strcmp(g_arg->argv[1], "-"))
		return (getenv("OLDPWD"));
	else if (!g_arg->argv[1])
		return (getenv("HOME"));
	else
		return (g_arg->argv[1]);
}

void			print_err_cd(char *path)
{
	if (!access(path, 0))
		ft_putstr_fd("cd : file not found", 2);
	if (!access(path, 0))
		ft_putstr_fd("cd : file not found", 2);
	else
		ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putendl_fd(path, 2);
}

void			exec_cd(void)
{
	char		*path;

	path = (g_arg->argv[1] ? g_arg->argv[1] : NULL);
	if (g_arg->argc <= 2 && g_arg->argc >= 1)
	{
		path = find_path();
		if (!path)
			path = ".";
		pwd_control("OLDPWD=");
		if (chdir(path) == -1)
			print_err_cd(path);
		else
			pwd_control("PWD=");
	}
	else
		print_err_cd(path);
}
