/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorobov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:54:43 by akorobov          #+#    #+#             */
/*   Updated: 2018/10/27 17:04:33 by akorobov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != 0)
	{
		f(&s[i]);
		i++;
	}
}
