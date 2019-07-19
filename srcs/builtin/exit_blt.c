/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 10:54:12 by efischer          #+#    #+#             */
/*   Updated: 2019/07/18 10:55:14 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_blt(char **av, t_list **lst)
{
	int		status;

	status = 0;
	if (av[1] != NULL)
		status = ft_atoi(av[1]);
	ft_free_tab(av);
	ft_lstfree(*lst, free_env);
	exit(status);
	return (status);
}
