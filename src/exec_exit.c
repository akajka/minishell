/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 22:21:21 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/09 22:30:52 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(t_arg *arg)
{
	int	i;

	i = -1;
	while (arg->argv[++i])
		ft_strdel(&arg->argv[i]);
	free(arg->argv);
	exit(EXIT_SUCCESS);
}
