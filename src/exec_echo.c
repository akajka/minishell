/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:33:21 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/12 22:22:49 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_echo(void)
{
	int		i;

	i = 0;
	while (++i < g_arg->argc)
	{
		if (i == 1 && !ft_strcmp(g_arg->argv[1], "-n"))
			continue ;
		write(1, g_arg->argv[i], ft_strlen(g_arg->argv[i]));
		write(1, " ", 1);
	}
	if (g_arg->argv[1] && ft_strcmp(g_arg->argv[1], "-n"))
		write(1, "\n", 1);
}
