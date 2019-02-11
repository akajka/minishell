/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getargv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:36:06 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/11 18:55:10 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				env_finder(char *tmp, t_arg *arg)
{
	int			j;

	j = -1;
	while (arg->env[++j] && ft_strncmp(arg->env[j], tmp, ft_strlen(tmp)))
		continue ;
	return (j);
}

void			manage_env(int *adr, t_arg *arg)
{
	int			i;
	int			j;
	char		buf[1024];
	char		tmp[1024];

	i = -1;
	while (++i >= 0 && arg->argv[arg->argc][*adr + i + 1] &&
			arg->argv[arg->argc][*adr + i + 1] != '$' &&
			arg->argv[arg->argc][*adr + i + 1] != '`')
		tmp[i] = arg->argv[arg->argc][*adr + i + 1];
	tmp[i] = '\0';
	j = env_finder(tmp, arg);
	ft_strcpy(buf, arg->argv[arg->argc]);
	ft_strclr(&buf[*adr]);
	if (arg->env[j])
		ft_strcat(buf, ft_strchr(arg->env[j], '=') + 1);
	if (arg->argv[arg->argc][*adr + i + 1])
		ft_strcat(buf, &arg->argv[arg->argc][*adr + i + 1]);
	ft_strdel(&arg->argv[arg->argc]);
	arg->argv[arg->argc] = ft_strdup(buf);
	*adr = (arg->argv[arg->argc][*adr] != '$' ? *adr +
			ft_strlen(ft_strchr(arg->env[j], '=') + 1) :
			ft_strlen(arg->argv[arg->argc]));
}

void			findchar(t_arg *arg, char c, int *count)
{
	int			val;
	int			i;

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

void			parse_buf(t_arg *arg, int i)
{
	if (arg->buf[0] == '\t')
		arg->buf[0] = ' ';
	while (arg->buf[++i] != '\0')
	{
		if (arg->buf[i] == '\"' && i - 1 >= 0 && arg->buf[i - 1] != '\\')
			findchar(arg, '\"', &i);
		else if (arg->buf[i] == '\'' && i - 1 >= 0 && arg->buf[i - 1] != '\\')
			findchar(arg, '\'', &i);
		else if (arg->buf[i] == '`' && i - 1 >= 0 && arg->buf[i - 1] != '\\')
			findchar(arg, '`', &i);
	}
	if (arg->buf[i - 1] == '\t')
		arg->buf[i - 1] = ' ';
}

void			getargv(t_arg *arg)
{
	int			i;

	arg->argc = -1;
	parse_buf(arg, -1);
	arg->argv = ft_strsplit(arg->buf, ' ');
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
