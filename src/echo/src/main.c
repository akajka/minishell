/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 21:19:35 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/04 02:02:57 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

int		main(int argc, char **argv)
{
	int		i;
	char	*adr;
	t_arg	arg;

	i = 1;
	arg.argv = (char **)malloc(sizeof(char *) * argc);
	arg.argc = -1;
	while (argc-- != 1)
	{
		if ((adr = ft_strchr(argv[i], '`')))
		{
			arg.argv[++arg.argc] = ft_strsub(argv[i], argv[i] - adr,
					ft_strlen(argv[i]));
			find_command(&arg);
		}
		else
			ft_putstr(argv[i++]);
		write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
