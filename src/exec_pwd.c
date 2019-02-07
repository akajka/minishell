/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:02:47 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/07 10:44:29 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_arg *arg)
{
	char	dir[1024];

	if (arg->argc == 1)
	{
		getcwd(dir, 1024);
		write(1, dir, ft_strlen(dir));
	}
	else
		write(2, "pwd: too many arguments", 23);
}
