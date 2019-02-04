/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:31:01 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/04 01:54:01 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		handle_arg(t_arg *arg, int *count)
{
	int		i;

	i = -1;
	if (arg->buf[0])
	{
		getargv(arg);
		find_command(arg);
		*count = -1;
		ft_strclr(arg->buf);
		while (arg->argv[++i])
			free(arg->argv[i]);
		free(arg->argv);
	}
	write(1, "minishell> ", 11);
}

void		ft_welcome(char c)
{
	if (c == '\n')
		write(1, "minishell> ", 11);
	else if (c == '\'')
		write(1, "quote> ", 8);
	else
		write(1, "bquote> ", 9);
}

void		loop(t_arg *arg, int *count, char c)
{
	char	buf[1];

	ft_welcome(c);
	if (c != '\n')
		arg->buf[++*count] = '\n';
	while (read(0, buf, 1))
	{
		if (buf[0] != '\n')
			arg->buf[++*count] = buf[0];
		else
		{
			if (c != '\n')
				break ;
			handle_arg(arg, count);
		}
	}
}

int			main()
{
	t_arg	*arg;
	int		count;

	count = -1;
	arg = (t_arg *)malloc(sizeof(arg));
	loop(arg, &count, '\n');
	return (EXIT_SUCCESS);
}
