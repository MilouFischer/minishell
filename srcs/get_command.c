/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 11:56:37 by efischer          #+#    #+#             */
/*   Updated: 2019/08/07 14:56:06 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_expansion(char **av, t_list *lst)
{
	size_t	i;

	i = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '~')
			process_tilde(&av[i], lst);
		if (ft_strchr(av[i], '$') != NULL)
		{
			if (process_dollar(&av[i], lst) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int			ft_get_command(char ***av, char *buf, t_list *lst)
{
	*av = ft_split_white_spaces(buf);
	if (*av == NULL)
		return (FALSE);
	if (check_expansion(*av, lst) == FAILURE)
	{
		g_ret = 1;
		return (FALSE);
	}
	return (TRUE);
}
