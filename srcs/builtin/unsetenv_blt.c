/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_blt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:50:40 by efischer          #+#    #+#             */
/*   Updated: 2019/08/05 13:55:48 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	del_env(char *av, t_list **lst)
{
	t_list	*del;
	t_list	*head;

	head = *lst;
	del = find_env(av, *lst);
	if (del == NULL)
		return ;
	if (*lst == del)
		*lst = del->next;
	else
	{
		while ((*lst)->next != NULL && (*lst)->next != del)
			*lst = (*lst)->next;
		(*lst)->next = del->next;
		*lst = head;
	}
	ft_lstdelone(&del, free_env);
}

int			unsetenv_blt(char **av, t_list **lst)
{
	size_t	i;

	av++;
	i = 0;
	if (*av == NULL)
	{
		ft_putendl_fd("minishell: unsetenv: Too few arguments", 2);
		return (FAILURE);
	}
	while (av[i] != NULL)
	{
		del_env(av[i], lst);
		i++;
	}
	return (SUCCESS);
}
