/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 23:10:13 by akorobov          #+#    #+#             */
/*   Updated: 2019/02/17 13:51:23 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		env_name(char *tmp1, int *i_tmp1, int *i)
{
	if (g_arg->stat.bq)
		while (g_arg->buf[*i] != '\0' && g_arg->buf[*i] != '/' &&
				status_argc(g_arg->buf, g_arg->buf[*i], *i) && g_arg->stat.bq)
			tmp1[(*i_tmp1)++] = g_arg->buf[(*i)++];
	else
		while (g_arg->buf[*i] != '\0' && g_arg->buf[*i] != '/' &&
				g_arg->buf[*i] != ' ' && g_arg->buf[*i] != '\t')
			tmp1[(*i_tmp1)++] = g_arg->buf[(*i)++];
}

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
	char	tmp[1024];

	count = -1;
	g_arg->env = (char **)malloc(sizeof(char *) * 1000);
	while (env[++count])
	{
		if (!ft_strncmp(env[count], "SHELL=", 6))
		{
			getcwd(tmp, 1024);
			ft_stracat(tmp, "SHELL=");
			ft_strcat(tmp, "/minishell");
			g_arg->env[count] = ft_strdup(tmp);
		}
		else
			g_arg->env[count] = ft_strdup(env[count]);
	}
	g_arg->env[count] = NULL;
	if (!env[0])
		create_env();
}

void		create_env(void)
{
	char	tmp[1024];

	g_arg->env[0] = ft_strdup("HOME=/Users/akorobov");
	g_arg->env[1] = ft_strdup("PATH=/usr/bin:/bin");
	getcwd(tmp, 1024);
	ft_stracat(tmp, "SHELL=");
	ft_strcat(tmp, "/minishell");
	g_arg->env[2] = ft_strdup(tmp);
	ft_strclr(tmp);
	g_arg->env[3] = NULL;
}
