/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getargv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:36:06 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/13 17:42:01 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				manage_env(int adr)
{
	int			i;
	int			j;
	char		buf[1024];
	char		tmp[1024];

	i = -1;
	while (++i >= 0 && g_arg->argv[g_arg->argc][adr + i + 1] &&
			g_arg->argv[g_arg->argc][adr + i + 1] != '/' &&
			g_arg->argv[g_arg->argc][adr + i + 1] != '$')
		tmp[i] = g_arg->argv[g_arg->argc][adr + i + 1];
	tmp[i] = '\0';
	if (!g_arg->env[(j = env_finder(tmp, ft_strlen(tmp)))])
		return (ft_strlen(g_arg->argv[g_arg->argc]));
	ft_strcpy(buf, g_arg->argv[g_arg->argc]);
	ft_strclr(&buf[adr]);
	if (g_arg->env[j])
		ft_strcat(buf, ft_strchr(g_arg->env[j], '=') + 1);
	if (g_arg->argv[g_arg->argc][adr + i + 1])
		ft_strcat(buf, &g_arg->argv[g_arg->argc][adr + i + 1]);
	ft_strdel(&g_arg->argv[g_arg->argc]);
	g_arg->argv[g_arg->argc] = ft_strdup(buf);
	return ((g_arg->argv[g_arg->argc][adr] != '$' ? adr +
			ft_strlen(ft_strchr(g_arg->env[j], '=') + 1) :
			ft_strlen(g_arg->argv[g_arg->argc])));
}

void			check_place(t_status *st, int i)
{
	if (st->position)
		g_arg->buf[st->position] = ' ';
	st->position = (st->position ? 0 : i);
	st->occurrence = !(st->occurrence);
}

void			parse_buf(void)
{
	t_status	bquote;
	t_status	quote;
	int			i;

	i = -1;
	bquote.occurrence = 0;
	quote.occurrence = 0;
	while (g_arg->buf[++i])
	{
		if (g_arg->buf[i] == '\"' && !quote.occurrence &&
				(i - 1 >= 0 ? g_arg->buf[i - 1] != '\\' : 1))
			check_place(&bquote, i);
		if (g_arg->buf[i] == '\'' && !bquote.occurrence &&
				(i - 1 >= 0 && g_arg->buf[i - 1] != '\\'))
			check_place(&quote, i);
		
	}
}

void			getargv(void)
{
	int			i;

	g_arg->argc = -1;
	parse_buf();
	g_arg->argv = ft_strsplit(g_arg->buf, ' ');
	while (g_arg->argv[++g_arg->argc])
	{
		if (!ft_strcmp(g_arg->argv[g_arg->argc], "~"))
		{
			ft_strdel(&g_arg->argv[g_arg->argc]);
			g_arg->argv[g_arg->argc] = ft_strdup("$HOME");
		}
		i = 0;
		while (g_arg->argv[g_arg->argc][i] == '$' ||
				(i = ft_strchr_int(&g_arg->argv[g_arg->argc][i], '$')))
			i = manage_env(i);
	}
	g_arg->argv[g_arg->argc] = NULL;
}
