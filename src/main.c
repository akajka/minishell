/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:31:01 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/17 02:45:52 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			clean_arg()
{
	int			i;

	i = -1;
	while (g_arg->argv && g_arg->argv[++i])
		ft_strdel(&g_arg->argv[i]);
	if (g_arg->argv)
		free(g_arg->argv);
	ft_strclr(g_arg->buf);
}

void			handle_g_arg()
{
	if (g_arg->buf[0] != '\0')
	{
		getargv();
		find_command();
		clean_arg();
	}
	if (g_arg->sig == 0)
		welcome();
}

void			welcome(void)
{
	ft_putstr("\033[1;36m");
	ft_putstr(g_arg->welcome_str);
	ft_putstr("\033[0m");
}

void			loop(void)
{
	int			count;
	char		buf[1];

	welcome();
	count = -1;
	while (1)
	{
		read(0, buf, 1);
		if (buf[0] != '\n' && buf[0] != ';')
			g_arg->buf[++count] = buf[0];
		else
		{
			g_arg->buf[++count] = '\0';
			g_arg->sig = (buf[0] == ';' ? 1 : 0);
			handle_g_arg();
			count = -1;
		}
	}
}

int				main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_arg = (t_arg *)malloc(sizeof(t_arg));
	g_arg->welcome_str = ft_strdup("minishell> ");
	env_cpy(env);
	signal(SIGINT, sig_handl);
	loop();
	return (EXIT_SUCCESS);
}
