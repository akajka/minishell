/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:02:47 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/12 23:21:53 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(void)
{
	char	dir[1024];

	if (g_arg->argc == 1)
	{
		getcwd(dir, 1024);
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	else
		write(2, "pwd: too many g_arguments\n", 24);
}
