/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv_blt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:13:22 by efischer          #+#    #+#             */
/*   Updated: 2019/07/09 15:03:18 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			printenv_blt(char **av, t_list **lst)
{
	t_list	*tmp;

	if (*lst == NULL)
		return ;
	if (av != NULL && *av == NULL)
		ft_lstprint(*lst, get_content_to_print);
	else
	{
		while (av != NULL && *av != NULL)
		{
			tmp = find_env(*av++, *lst);
			if (tmp != NULL)
				ft_putendl(((t_env*)(tmp->content))->value);
		}
	}
}
