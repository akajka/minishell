/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:55:11 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/12 23:21:33 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exec_cd(void)
{
	if (g_arg->argc <= 2 && g_arg->argc >= 1)
	{
		if ((g_arg->argv[1] ? chdir(g_arg->argv[1]) :
					chdir(get_env("HOME"))) == -1)
		{
			write(2, "cd: no such file or directory: ", 31);
			ft_putstr_fd(g_arg->argv[1] ? g_arg->argv[1] :
						get_env("HOME"), 2);
			write(2, "\n", 1);
		}
	}
	else
	{
		write(2, "cd: string not in pwd: ", 23);
		write(2, g_arg->argv[1], ft_strlen(g_arg->argv[1]));
		write(2, "\n", 1);
	}
}
