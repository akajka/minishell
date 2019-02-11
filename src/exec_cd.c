/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:55:11 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/11 22:24:22 by akorobov         ###   ########.fr       */
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
	tmp.env = arg->env;
	getargv(&tmp);
	exec_setenv(&tmp);
	i = -1;
	while (tmp.argv[++i])
		ft_strdel(&tmp.argv[i]);
	free(tmp.argv);
}

void			getoldpwd(t_arg *arg)
{
	int			i;

	i = -1;
	ft_strdel(&arg->argv[1]);
	if (arg->oldpwd[0] != '\0')
		arg->argv[1] = ft_strdup(arg->oldpwd);
	else
	{
		while (ft_strncmp(arg->env[++i], "OLDPWD", 6))
			continue ;
		arg->argv[1] = ft_strdup(ft_strchr(arg->env[i], '='));
	}
}

char			*gethome(char **env)
{
	int			i;

	i = 0;
	while (ft_strncmp(env[++i], "HOME", 4))
		continue ;
	return (ft_strchr(env[i], '=') + 1);
}

void			exec_cd(t_arg *arg)
{
	if (arg->argc <= 2 && arg->argc >= 1)
	{
		if (arg->argv[1] && !ft_strcmp(arg->argv[1], "-"))
			getoldpwd(arg);
		croldpwd(arg);
		if ((arg->argv[1] ? chdir(arg->argv[1]) :
					chdir(gethome(arg->env))) == -1)
		{
			write(2, "cd: no such file or directory: ", 31);
			write(2, (arg->argv[1] ? arg->argv[1] :
						gethome(arg->env)), ft_strlen(arg->argv[1]));
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
