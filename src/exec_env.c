/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:14:15 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/07 10:44:29 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_env(t_arg *arg)
{
	int		count;

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
}

void		exec_setenv(t_arg *arg)
{
	int		i;
	int		n;

	if (arg->argc == 2)
	{
		n = 0;
		while (arg->argv[1][n] && arg->argv[1][n] != '=')
			n++;
		if (!arg->argv[1][n])
			write(2, "usage setenv\n", 13);
		else
		{
			i = -1;
			while (environ[++i] && ft_strncmp(environ[i], arg->argv[1], n))
				continue ;
			if (environ[i])
				ft_strclr(environ[i]);
			else
				environ[i] = (char *)malloc(ft_strlen(arg->argv[1]));
			ft_strcpy(environ[i], arg->argv[1]);
			environ[i + 1] = NULL;
		}
	}
	else
		write(2, "usage setenv\n", 13);
}

void		exec_unsetenv(t_arg *arg)
{
	int		i;

	i = -1;
	if (arg->argc == 2)
	{
		while (environ[++i] && ft_strncmp(environ[i], arg->argv[1],
					ft_strlen(arg->argv[1])))
			continue ;
		if (environ[i])
			ft_strclr(environ[i]);
		else
			write(2, "variable not found\n", 19);
	}
	else
		write(2, "usage unsetenv\n", 15);
}
