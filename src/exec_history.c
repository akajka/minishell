/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:44:29 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/06 15:01:51 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_history(t_arg *arg)
{
	t_list	*p;

	p = arg->history;
	while (p)
	{
		if (p->content)
			ft_putendl(p->content);
		p = p->next;
	}
}
