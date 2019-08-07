/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:18:40 by efischer          #+#    #+#             */
/*   Updated: 2019/08/07 19:19:13 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bracket(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '{' && str[i] != '}')
		i++;
	if (str[i] == '\0' || str[i] == '}')
		return (SUCCESS);
	if (str[i + 1] == '}')
		return (FAILURE);
	i++;
	while (str[i] != '\0' && str[i] != '}')
	{
		if (str[i] == '{')
			return (FAILURE);
		i++;
	}
	if (str[i] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

int			check_bracket(char *str)
{
	char	**tab;
	size_t	i;

	i = 0;
	tab = ft_strsplit(str, '$');
	if (tab == NULL)
		return (FAILURE);
	while (tab[i] != NULL)
	{
		if (bracket(tab[i]) == FAILURE)
		{
			ft_free_tab(tab);
			return (FAILURE);
		}
		i++;
	}
	ft_free_tab(tab);
	return (SUCCESS);
}
