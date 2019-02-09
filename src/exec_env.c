/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:14:15 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/09 22:33:12 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exec_env(t_arg *arg)
{
	extern char **environ;
	int			count;

	count = -1;
	if (arg->argc < 2)
		while (environ[++count])
		{
			write(1, environ[count], ft_strlen(environ[count]));
			if (environ[count + 1] && environ[count + 1][0])
				write(1, "\n", 1);
		}
	else
		write(2, "pwd: too many arguments", 23);
	write(2, "\n", 1);
}

void			exec_setenv(t_arg *arg)
{
	extern char **environ;
	int			i;
	int			n;

	n = (arg->argc == 2 ? ft_strchr_int(arg->argv[1], '=') : 0);
	if (n)
	{
		i = -1;
		while (environ[++i] && ft_strncmp(environ[i], arg->argv[1], n))
			continue ;
		if (environ[i])
			ft_strclr(environ[i]);
		else
		{
			environ[i] = (char *)malloc(ft_strlen(arg->argv[1]) + 1);
			environ[i + 1] = NULL;
		}
		ft_strcpy(environ[i], arg->argv[1]);
	}
	else
		write(2, "usage setenv\n", 13);
}

void			exec_unsetenv(t_arg *arg)
{
	extern char **environ;
	int			i;

	i = -1;
	if (arg->argc == 2)
	{
		i = env_finder(arg->argv[1]);
		if (environ[i])
			ft_strclr(environ[i]);
		else
			write(2, "variable not found\n", 19);
	}
	else
		write(2, "usage unsetenv\n", 15);
}
