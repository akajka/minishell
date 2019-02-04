/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getargv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:36:06 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/04 21:32:51 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		findchar(t_arg *arg, char c, int *count)
{
	int		val;
	int		i;

	val = 0;
	i = *count;
	while (arg->buf[++i])
		if (arg->buf[i] == c && ++val)
			break ;
	if (!val)
	{
		i--;
		loop(arg, &i, c);
		parse_buf(arg, *count - 1);
	}
	*count += i;
}

void		parse_buf(t_arg *arg, int i)
{
	while (arg->buf[++i] != '\0')
	{
		if (arg->buf[i] == '\t')
			arg->buf[i] = ' ';
		else if (arg->buf[i] == '\"')
			findchar(arg, '\"', &i);
		else if (arg->buf[i] == '\'')
			findchar(arg, '\'', &i);
		else if (arg->buf[i] == '`')
			findchar(arg, '`', &i);
	}
}

void		getargv(t_arg *arg)
{
	arg->argc = 0;
	parse_buf(arg, -1);
	arg->argv = ft_strsplit(arg->buf, ' ');
	while (arg->argv[++arg->argc])
		continue ;
	arg->argv[arg->argc] = NULL;
}
