/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 23:10:13 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/13 02:34:26 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			env_finder(char *env, int len)
{
	int		j;

	j = -1;
	while (g_arg->env[++j] && ft_strncmp(g_arg->env[j], env, len))
		continue ;
	return (j);
}

char		*get_env(char *env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(env);
	while (g_arg->env[i] && ft_strncmp(g_arg->env[i], env, len))
		i++;
	if (g_arg->env[i])
		return (ft_strchr(g_arg->env[i], '=') + 1);
	else
		return (NULL);
}

void		env_cpy(char **env)
{
	int		count;

	count = -1;
	while (env[++count])
		continue ;
	if (count)
	{
		g_arg->env = (char **)malloc(sizeof(char *) * (count + 1));
		g_arg->env[count] = NULL;
		while (--count >= 0)
			g_arg->env[count] = ft_strdup(env[count]);
	}
}
