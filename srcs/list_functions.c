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
	tmp = ft_asprintf("%s=%s\n", ((t_env*)(lst->content))->name,
	((t_env*)(lst->content))->value);
	*elem = ft_lstnew(tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
}

char	*get_content_to_tab(t_list *lst)
{
	char	*tmp;

	tmp = ft_asprintf("%s=%s", ((t_env*)(lst->content))->name,
	((t_env*)(lst->content))->value);
	return (tmp);
}

void	free_env(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_env*)content)->name);
	ft_strdel(&((t_env*)content)->value);
	free(content);
}
