/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:33:21 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/04 22:24:03 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		output_echo(char *argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] != '\"' || (i - 1 > 0 && argv[i - 1] == '\\'))
			write(1, &argv[i], 1);
		i++;
	}
}

int			handle_echo(char *adr)
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
		if (count % 2 == 0)
			ret = find_command(&tmp_arg);
		free(tmp_arg.argv[count]);
	}
	free(tmp_arg.argv);
	return (ret);
}

void		exec_echo(t_arg *arg)
{
	int		i;
	int		ret;
	char	*adr;

	i = 1;
	ret = 0;
	while (arg->argc-- != 1)
	{
		if ((adr = ft_strchr(arg->argv[i], '`')))
		{
			ret = handle_echo(adr);
			ft_strdel(&adr);
		}
		else
			output_echo(arg->argv[i++]);
	}
	if (!ret)
		write(1, "\n", 1);
}
