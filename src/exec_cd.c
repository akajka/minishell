/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:55:11 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/09 22:31:20 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			croldpwd(t_arg *arg)
{
	int			i;
	t_arg		tmp;

	tmp.argc = 2;
	ft_strclr(arg->oldpwd);
	ft_strcpy(tmp.buf, "setenv OLDPWD=");
	getcwd(arg->oldpwd, 1024);
	ft_strcat(tmp.buf, arg->oldpwd);
	getargv(&tmp);
	exec_setenv(&tmp);
	i = -1;
	while (tmp.argv[++i])
		ft_strdel(&tmp.argv[i]);
	free(tmp.argv);
}

void			getoldpwd(t_arg *arg)
{
	extern char **environ;
	int			i;

	i = -1;
	ft_strdel(&arg->argv[1]);
	if (arg->oldpwd[0] != '\0')
		arg->argv[1] = ft_strdup(arg->oldpwd);
	else
	{
		while (ft_strncmp(environ[++i], "OLDPWD", 6))
			continue ;
		arg->argv[1] = ft_strsub(environ[i], 7, ft_strlen(environ[i]));
	}
}

void			exec_cd(t_arg *arg)
{
	if (arg->argc <= 2 && arg->argc >= 1)
	{
		if ((arg->argc == 1 || !arg->argv[1]) && arg->argc++)
		{
			arg->argv[1] = ft_strdup(".");
			arg->argv[2] = NULL;
		}
		if (!ft_strcmp(arg->argv[1], "-"))
			getoldpwd(arg);
		croldpwd(arg);
		if (chdir(arg->argv[1]) == -1)
		{
			write(2, "cd: no such file or directory: ", 31);
			write(2, arg->argv[1], ft_strlen(arg->argv[1]));
			write(2, "\n", 1);
		}
	}
	else
	{
		write(2, "cd: string not in pwd: ", 23);
		write(2, arg->argv[1], ft_strlen(arg->argv[1]));
		write(2, "\n", 1);
	}
}
