/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:31:01 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/07 20:57:27 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handle_arg(t_arg *arg, int *count)
{
	int		i;

	i = -1;
	if (arg->buf[0] != '\0')
	{
		getargv(arg);
		find_command(arg);
		*count = -1;
		ft_strclr(arg->buf);
		while (arg->argv[++i])
			ft_strdel(&arg->argv[i]);
		free(arg->argv);
	}
	ft_putstr("\033[1;36m");
	write(1, "minishell> ", 11);
	ft_putstr("\033[0m");
}

void		ft_welcome(char c)
{
	ft_putstr("\033[1;36m");
	if (c == '\n')
		write(1, "minishell> ", 11);
	else if (c == '\\')
		write(1, "> ", 2);
	else if (c == '\'')
		write(1, "quote> ", 8);
	else
		write(1, "bquote> ", 9);
	ft_putstr("\033[0m");
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
			arg->buf[++*count] = '\0';
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
	arg->col_cmd = 0;
	arg->parse->single_quote = 0;
	arg->parse->double_quote = 0;
	arg->parse->binary_quote = 0;
	arg->parse->slash = 0;
	arg->history = (t_list *)malloc(sizeof(t_list));
	arg->history->content = NULL;
	arg->history->next = NULL;
	arg->cd = (t_list *)malloc(sizeof(t_list));
	arg->cd->content = NULL;
	arg->cd->next = NULL;
	loop(arg, &count, '\n');
	return (EXIT_SUCCESS);
}
