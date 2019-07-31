/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 10:54:12 by efischer          #+#    #+#             */
/*   Updated: 2019/07/31 17:11:47 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		exit_blt(char **av, t_list **lst)
{
	int		status;

	status = EXIT_SUCCESS;
	ft_putendl_fd("exit", 2);
	if (av[1] != NULL && (ft_str_is_numeric(av[1]) == FALSE || ft_atoi_ul(av[1]) > LLONG_MAX))
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
	else if (ft_tablen(av) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (FAILURE);
	}
	if (av != NULL && av[1] != NULL)
		status = ft_atoi(av[1]);
	ft_free_tab(av);
	ft_lstfree(*lst, free_env);
	exit(status);
}
