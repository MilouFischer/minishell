/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:08:56 by efischer          #+#    #+#             */
/*   Updated: 2019/06/18 15:14:52 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_content_to_print(t_list *lst, t_list **elem)
{
	char	*tmp;

	ft_bzero(elem, sizeof(*elem));
	tmp = ft_strdup(((t_env*)(lst->content))->all);
	tmp = ft_join_free(tmp, "\n", 1);
	*elem = ft_lstnew(tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
}

char	*get_content_to_tab(t_list *lst)
{
	return (ft_strdup(((t_env*)(lst->content))->all));
}

void	free_env(void *content)
{
	ft_strdel(&((t_env*)content)->name);
	ft_strdel(&((t_env*)content)->value);
	ft_strdel(&((t_env*)content)->all);
	free(content);
}
