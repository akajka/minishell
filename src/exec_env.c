/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:14:15 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/12 23:47:53 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void			exec_env(void)
{
	int			count;

	count = -1;
	if (g_arg->argc < 2)
		while (g_arg->env[++count])
		{
			write(1, g_arg->env[count], ft_strlen(g_arg->env[count]));
			if (g_arg->env[count + 1] && g_arg->env[count + 1][0])
				write(1, "\n", 1);
		}
	else
		write(2, "env: too many g_arguments", 23);
	write(2, "\n", 1);
}

void			exec_setenv(char *env)
{
	int			i;
	int			n;

	n = ((g_arg->argc == 2 && env) ? ft_strchr_int(env, '=') : 0);
	if (n)
	{
		i = env_finder(env, n);
		if (g_arg->env[i])
			ft_strdel(&g_arg->env[i]);
		else
			g_arg->env[i] = NULL;
		g_arg->env[i] = ft_strdup(g_arg->argv[1]);
	}
	else
		write(2, "\n", 13);
}

void			exec_unsetenv(char *env)
{
	int			i;

	i = -1;
	if (g_arg->argc == 2 && env)
	{
		i = env_finder(env, ft_strlen(env));
		if (g_arg->env[i])
		{
			ft_strdel(&g_arg->env[i--]);
			while (g_arg->env[++i + 1])
				g_arg->env[i] = g_arg->env[i + 1];
			g_arg->env[i] = NULL;
		}
		else
			write(2, "variable not found\n", 19);
	}
	else
		write(2, "usage unsetenv\n", 15);
}
