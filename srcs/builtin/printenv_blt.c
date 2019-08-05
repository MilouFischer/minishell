/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv_blt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:13:22 by efischer          #+#    #+#             */
/*   Updated: 2019/08/05 10:51:06 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		printenv_blt(char **av, t_list **lst)
{
	if (ft_strequ(av[0], "printenv") == TRUE)
		av++;
	if (av != NULL && *av == NULL)
	{
		print_env(*lst, "printenv");
	}
	else if (*lst == NULL)
		return (FAILURE);
	else
	{
		while (av != NULL && *av != NULL)
		{
			print_env_one(*lst, "printenv", *av);
			av++;
		}
	}
	return (SUCCESS);
}
