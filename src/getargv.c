/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getargv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:36:06 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/07 20:04:56 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		manage_env(int *adr, t_arg *arg)
{
	int		i;
	int		j;
	char	*env;
	char	buf[1024];
	char	tmp[1024];

	i = -1;
	while (++i >= 0 && arg->argv[arg->argc][*adr + i + 1] &&
			arg->argv[arg->argc][*adr + i + 1] != ' ' &&
			arg->argv[arg->argc][*adr + i + 1] != '$' &&
			arg->argv[arg->argc][*adr + i + 1] != '`')
			tmp[i] = arg->argv[arg->argc][*adr + i + 1];
	tmp[i] = '\0';
	j = -1;
	while (environ[++j] && ft_strncmp(environ[j], tmp, ft_strlen(tmp)))
		continue ;
	ft_strcpy(buf, arg->argv[arg->argc]);
	ft_strclr(&buf[*adr]);
	if (environ[j])
		ft_strcat(buf, (env = ft_strchr(environ[j], '=') + 1));
	if (arg->argv[arg->argc][*adr + i + 1])
		ft_strcat(buf, &arg->argv[arg->argc][*adr + i + 1]);
	ft_strdel(&arg->argv[arg->argc]);
	arg->argv[arg->argc] = ft_strdup(buf);
	*adr = (arg->argv[arg->argc][*adr] != '$' ? *adr + ft_strlen(env):
				ft_strlen(arg->argv[arg->argc]));
}

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
	*count = i;
}

void		add_elem_history(t_arg *arg)
{
	t_list	*tmp;
	t_list	*p;

	tmp = (t_list *)malloc(sizeof(t_list));
	p = arg->history->next;
	arg->history->next = tmp;
	tmp->content = ft_strdup(arg->buf);
	tmp->next = p;
}

void		getargv(t_arg *arg)
{
	int		i;

	arg->argc = -1;
	
	if (!ft_strncmp(arg->argv[0], "history", 7))
		add_elem_history(arg);
	while (arg->argv[++arg->argc])
	{
		if (!ft_strcmp(arg->argv[arg->argc], "~"))
		{
			ft_strdel(&arg->argv[arg->argc]);
			arg->argv[arg->argc] = ft_strdup("$HOME");
		}
		i = 0;
		while (arg->argv[arg->argc][i] == '$' ||
				(i = ft_strchr_int(&arg->argv[arg->argc][i], '$')))
			manage_env(&i, arg);
	}
	arg->argv[arg->argc] = NULL;
}
