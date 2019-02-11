/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:31:01 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/11 22:36:25 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			handle_arg(t_arg *arg, int *count)
{
	int			i;

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
	if (arg->sig == 0)
	{
		*count = -1;
		ft_putstr("\033[1;36m");
		write(1, "minishell> ", 11);
		ft_putstr("\033[0m");
	}
}

void			ft_welcome(char c)
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

void			loop(t_arg *arg, int *count, char c)
{
	char		buf[1];

	ft_welcome(c);
	if (c != '\n')
		arg->buf[++*count] = '\n';
	while (read(0, buf, 1))
	{
		if (buf[0] != '\n' && buf[0] != ';')
			arg->buf[++*count] = buf[0];
		else
		{
			if (buf[0] == ';' && ft_strchr_int(arg->buf, '"') % 2)
				continue ;
			arg->buf[++*count] = '\0';
			arg->sig = (buf[0] == ';' ? 1 : 0);
			if (c != '\n')
				break ;
			handle_arg(arg, count);
		}
	}
}

void			env_cpy(t_arg *arg)
{
	extern char	**environ;
	int			count;

	count = -1;
	while (environ[++count])
		continue ;
	arg->env = (char **)malloc(sizeof(char *) * (count + 1));
	arg->env[count] = NULL;
	while (--count >= 0)
		arg->env[count] = ft_strdup(environ[count]);
}

int				main(void)
{
	t_arg		*arg;
	int			count;

	arg = (t_arg *)malloc(sizeof(arg));
	env_cpy(arg);
	signal(SIGINT, sig_handl);
	count = -1;
	loop(arg, &count, '\n');
	return (EXIT_SUCCESS);
}
