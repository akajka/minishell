/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:55:11 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/04 20:53:39 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_cd(t_arg *arg)
{
	if (arg->argc <= 2 && arg->argc >= 1)
	{
		if (arg->argc == 1 || !arg->argv[1])
			arg->argv[arg->argc++] = ft_strdup(".");
		if (chdir(arg->argv[1]) == -1)
		{
			write(2, "cd: no such file or directory:", 30);
			write(2, arg->argv[1], ft_strlen(arg->argv[1]));
			write(2, "\n", 1);
		}
	}
	else
	{
		write(2, "cd: string not in pwd:", 22);
		write(2, arg->argv[1], ft_strlen(arg->argv[1]));
		write(2, "\n", 1);
	}
}
