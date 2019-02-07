/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:55:11 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/07 10:44:29 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handle_noun_cd(t_arg *arg)
{
	int		i;
	t_list	*p;

	i = 1;
	if (ft_strlen(arg->argv[1]) != 1)
		i = ft_atoi(&arg->argv[1][1]);
	p = arg->cd->next;
	while (i-- && p)
		p = p->next;
	ft_strdel(&arg->argv[1]);
	if (!i)
	{
		if (p && p->content)
			arg->argv[1] = ft_strdup(p->content);
		ft_strdel((char **)&p->content);
		free(p);
	}
}

void		get_pwd_cd(t_arg *arg)
{
	char	dir[1024];
	t_list	*p;
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	p = arg->cd->next;
	arg->cd->next = tmp;
	getcwd(dir, 1024);
	tmp->content = ft_strdup(dir);
	tmp->next = p;
}

void		exec_cd(t_arg *arg)
{
	get_pwd_cd(arg);
	if (arg->argc <= 2 && arg->argc >= 1)
	{
		if (arg->argv[1][0] == '-')
			handle_noun_cd(arg);
		if (arg->argc == 1 || !arg->argv[1])
			arg->argv[1] = ft_strdup(".");
		if (chdir(arg->argv[1]) == -1)
		{
			write(2, "cd: no such file or directory: ", 31);
			write(2, arg->argv[1], ft_strlen(arg->argv[1]));
			write(2, "\n", 1);
		}
	}
	else
	{
		write(2, "cd: string not in pwd: ", 23);
		write(2, arg->argv[1], ft_strlen(arg->argv[1]));
		write(2, "\n", 1);
	}
}
