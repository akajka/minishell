/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getargv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:36:06 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/17 02:55:19 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				status_argc(char c, int i)
{
	if (c == '\"' && (i >= 1 ? g_arg->buf[i - 1] != '\\' : 1)
			&& !g_arg->stat.q)
		g_arg->stat.bq = !(g_arg->stat.bq);
	else if (c == '\'' && (i >= 1 ? g_arg->buf[i - 1] != '\\' : 1)
			&& !g_arg->stat.bq)
		g_arg->stat.q = !(g_arg->stat.q);
	else if (!g_arg->stat.bq && !g_arg->stat.q && (c == ' ' || c == '\t'))
		return (0);
	return (1);
}

int				getargc(void)
{
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	while (g_arg->buf[i] != '\0' && ++ret)
	{
		if (g_arg->buf[i] == '\t' || g_arg->buf[i] == ' ')
			while (g_arg->buf[i] != '\0' &&
					(g_arg->buf[i] == ' ' || g_arg->buf[i] == '\t'))
				i++;
		if (!ft_strlen(&g_arg->buf[i]))
			return (ret - 1);
		while (g_arg->buf[i] != '\0' && status_argc(g_arg->buf[i], i))
			i++;
	}
	return (ret);
}

void			handle_buf()
{
	int			i;
	int			j;
	int			argc;
	char		tmp[1024];

	i = 0;
	argc = -1;
	while (g_arg->buf[i] != '\0' && ++argc < g_arg->argc)
	{
		j = 0;
		if (g_arg->buf[i] == '\t' || g_arg->buf[i] == ' ')
			while (g_arg->buf[i] != '\0' &&
					(g_arg->buf[i] == ' ' || g_arg->buf[i] == '\t'))
				i++;
		while (g_arg->buf[i] != '\0' && status_argc(g_arg->buf[i], i))
			tmp[j++] = g_arg->buf[i++];
		tmp[j] = '\0';
		g_arg->argv[argc] = ft_strdup(tmp);
		ft_strclr(tmp);
	}
}

void			getargv(void)
{
	g_arg->stat.bq = 0;
	g_arg->stat.q = 0;
	g_arg->argc = getargc();
	g_arg->argv = (char **)malloc(sizeof(char *) * (g_arg->argc + 1));
	handle_buf();
	g_arg->argv[g_arg->argc] = NULL;
}
