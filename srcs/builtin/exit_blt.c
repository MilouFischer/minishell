/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 10:54:12 by efischer          #+#    #+#             */
/*   Updated: 2019/07/31 17:44:58 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	compare_to_ulmax(char *str)
{
	size_t	len;
	size_t	long_max_len;

	len = ft_strlen(str);
	long_max_len = ft_strlen(S_LONG_MAX);
	if (len > long_max_len)
		return (FALSE);
	else if (len == long_max_len)
	{
		if (ft_strcmp(str, S_LONG_MAX) > 0)
			return (FALSE);
	}
	return (TRUE);
}

/*Print error with ft_dprint when it is done*/

int			exit_blt(char **av, t_list **lst)
{
	int		status;

	status = EXIT_SUCCESS;
	ft_putendl_fd("exit", 2);
	if (av != NULL && av[1] != NULL && (ft_str_is_numeric(av[1]) == FALSE
		|| compare_to_ulmax(av[1]) == FALSE))
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
