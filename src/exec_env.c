/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:14:15 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/11 18:56:03 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exec_env(t_arg *arg)
{
	int			count;

	count = -1;
	if (arg->argc < 2)
		while (arg->env[++count])
		{
			write(1, arg->env[count], ft_strlen(arg->env[count]));
			if (arg->env[count + 1] && arg->env[count + 1][0])
				write(1, "\n", 1);
		}
	else
		write(2, "pwd: too many arguments", 23);
	write(2, "\n", 1);
}

void			exec_setenv(t_arg *arg)
{
	int			i;
	int			n;

	n = (arg->argc == 2 ? ft_strchr_int(arg->argv[1], '=') : 0);
	if (n)
	{
		i = -1;
		while (arg->env[++i] && ft_strncmp(arg->env[i], arg->argv[1], n))
			continue ;
		if (arg->env[i])
			ft_strdel(&arg->env[i]);
		else
			arg->env[i + 1] = NULL;
		arg->env[i] = ft_strdup(arg->argv[1]);
	}
	else
		write(2, "usage setenv\n", 13);
}

void			exec_unsetenv(t_arg *arg)
{
	int			i;

	i = -1;
	if (arg->argc == 2)
	{
		i = env_finder(arg->argv[1], arg);
		if (arg->env[i])
			ft_strdel(&arg->env[i]);
		else
			write(2, "variable not found\n", 19);
	}
	else
		write(2, "usage unsetenv\n", 15);
}
