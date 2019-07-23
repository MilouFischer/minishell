/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_blt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:50:40 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 12:38:45 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		unsetenv_blt(char **av, t_list **lst)
{
	t_list	*head;
	t_list	*del_env;

	av++;
	head = *lst;
	if (*av == NULL)
		return (FAILURE);
	del_env = find_env(*av, *lst);
	if (del_env == NULL)
		return (SUCCESS);
	if (*lst == del_env)
		*lst = del_env->next;
	else
	{
		while ((*lst)->next != NULL && (*lst)->next != del_env)
			*lst = (*lst)->next;
		(*lst)->next = del_env->next;
		*lst = head;
	}
	ft_lstdelone(&del_env, free_env);
	return (SUCCESS);
}
