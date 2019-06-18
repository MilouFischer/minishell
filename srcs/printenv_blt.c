/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv_blt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:13:22 by efischer          #+#    #+#             */
/*   Updated: 2019/06/18 14:19:12 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		get_content(t_list *lst, t_list **elem)
{
	char	*tmp;

	ft_bzero(elem, sizeof(*elem));
	tmp = ft_strdup(((t_env*)(lst->content))->all);
	tmp = ft_join_free(tmp, "\n", 1);
	*elem = ft_lstnew(tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
}

void			printenv_blt(char **av, t_list *lst)
{
	t_list	*tmp;

	if (*av == NULL)
		ft_lstprint(lst, get_content);
	else
	{
		while (*av != NULL)
		{
			tmp = find_env(*av++, lst);
			ft_putendl(((t_env*)(tmp->content))->value);
		}
	}
}
