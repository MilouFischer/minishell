/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:17:20 by efischer          #+#    #+#             */
/*   Updated: 2019/06/15 16:18:45 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstprint(t_list *lst)
{
	while (lst != NULL)
	{
		ft_putendl(((t_env*)(lst->content))->all);
		lst = lst->next;
	}
}
