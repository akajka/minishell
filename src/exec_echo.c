/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:33:21 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/08 16:30:36 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			output_echo(char *argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if ((argv[i] != '\"' && argv[i] != '`' && (argv[i] != '\'' ||
						(argv[i] == '\'' && i - 1 >= 0 &&
						 ft_strchr(argv, '\"')))) ||
				(i - 1 > 0 && argv[i - 1] == '\\'))
				write(1, &argv[i], 1);
		if (argv[i] == '`')
			return (i);
		i++;
	}
	return (i);
}

void		handle_echo(char *adr)
{
	t_arg	tmp_arg;
	int		count;
	int		ret;

	tmp_arg.argv = ft_strsplit(adr, '`');
	tmp_arg.argc = 1;
	count = -1;
	ret = 0;
	while (tmp_arg.argv[++count])
	{
		find_command(&tmp_arg);
		free(tmp_arg.argv[count]);
	}
	free(tmp_arg.argv);
}

void		exec_echo(t_arg *arg)
{
	int		i;
	int		j;

	i = 1;
	while (arg->argc-- != 1)
	{
		j = output_echo(arg->argv[i]);
		if (arg->argv[i][j] == '`')
			handle_echo(&arg->argv[i][j]);
		write(1, " ", 1);
	}
	write(1, "\n", 1);
}
