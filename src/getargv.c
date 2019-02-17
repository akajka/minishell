/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getargv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:36:06 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/17 13:33:48 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				status_argc(char *buf, char c, int i)
{
	if (c == '\"' && (i >= 1 ? buf[i - 1] != '\\' : 1)
			&& !g_arg->stat.q)
		g_arg->stat.bq = !(g_arg->stat.bq);
	else if (c == '\'' && (i >= 1 ? buf[i - 1] != '\\' : 1)
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
		while (g_arg->buf[i] != '\0' &&
				status_argc(g_arg->buf, g_arg->buf[i], i))
			i++;
	}
	return (ret);
}

void			add_part(char *tmp, int	*i, int *i_tmp)
{
	char		tmp1[1024];
	char		*env;
	int			i_tmp1;

	i_tmp1 = 0;
	if (((g_arg->buf[*i] == '\"' && !g_arg->stat.q) ||
					(g_arg->buf[*i] == '\'' && !g_arg->stat.bq) ||
					g_arg->buf[*i] == '\\') &&
				(*i >= 1 ? g_arg->buf[*i - 1] != '\\' : 1))
		*i_tmp -= 1;
	else if (g_arg->buf[*i] == '$' && (*i >= 1 ?
				g_arg->buf[*i - 1] != '\\' : 1) && !g_arg->stat.q && ++(*i))
	{
		if (g_arg->stat.bq)
			while (g_arg->buf[*i] != '\0' && g_arg->buf[*i] != '/' &&
					status_argc(g_arg->buf, g_arg->buf[*i], *i) && g_arg->stat.bq)
				tmp1[i_tmp1++] = g_arg->buf[(*i)++];
		else
			while (g_arg->buf[*i] != '\0' && g_arg->buf[*i] != '/' &&
					g_arg->buf[*i] != ' ' && g_arg->buf[*i] != '\t')
				tmp1[i_tmp1++] = g_arg->buf[(*i)++];
		*i -= 1;
		tmp1[i_tmp1++] = '=';
		tmp1[i_tmp1] = '\0';
		ft_strcat(tmp, (env = get_env(tmp1)));
		*i_tmp += ft_strlen(env) - 1;
	}
	else
		tmp[*i_tmp] = g_arg->buf[*i];
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
		while (g_arg->buf[i] != '\0' &&
				status_argc(g_arg->buf, g_arg->buf[i], i))
		{
			add_part(tmp, &i, &j);
			i++;
			j++;
		}
		tmp[j] = '\0';
		g_arg->argv[argc] = ft_strdup(tmp);
		printf("%s\n", g_arg->argv[argc]);
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
