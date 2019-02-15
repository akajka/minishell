/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:19:25 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/13 23:03:16 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_handl(int sig)
{
	pid_t	pid;

	pid = getpid();
	if (sig == SIGINT && pid == 0)
		kill(pid, SIGINT);
	else
	{
		write(1, "\n", 1);
		if (g_arg->buf[0] == '\0')
			welcome();
//		clean_arg();
//		loop();
	}
}