/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_blt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 11:38:36 by efischer          #+#    #+#             */
/*   Updated: 2019/07/09 13:06:35 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*check_name(const char *name, t_list *lst)
{
	while (lst != NULL)
	{
		if (ft_strequ(name, ((t_env*)(lst->content))->name) == TRUE)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static void		add_env(const char *name, const char *val, t_list **lst)
{
	t_env	env;

	ft_bzero(&env, sizeof(env));
	env.name = ft_strdup(name);
	env.value = ft_strdup(val);
	ft_lstaddend(lst, ft_lstnew(&env, sizeof(env)));
}

int				setenv_blt(char **av, t_list **lst)
{
	t_list	*head;

	head = *lst;
	if (*av == NULL || lst == NULL)
		return (FAILURE);
	if (ft_strchr(*av, '=') != NULL)
		return (FAILURE);
	*lst = check_name(*av, *lst);
	if (*lst != NULL)
	{
		ft_strdel(&((t_env*)((*lst)->content))->value);
		((t_env*)((*lst)->content))->value = ft_strdup(av[1]);
	}
	else
		add_env(av[0], av[1], &head);
	*lst = head;
	return (SUCCESS);
}
