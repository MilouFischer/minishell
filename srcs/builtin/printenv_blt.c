/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv_blt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:13:22 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 12:38:06 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		printenv_blt(char **av, t_list **lst)
{
	t_list	*tmp;

	if (ft_strequ(av[0], "printenv") == TRUE)
		av++;
	if (av != NULL && *av == NULL)
	{
		print_env(*lst, "printenv");
	}
	else if (*lst == NULL)
		return (FAILURE);
	else
	{
		while (av != NULL && *av != NULL)
		{
			tmp = find_env(*av++, *lst);
			if (tmp != NULL && ft_strequ(((t_env*)(tmp->content))->name, "RET")
				== FALSE)
			{
				if (ft_putendl(((t_env*)(tmp->content))->value) == FAILURE)
					ft_putendl_fd("minishell: printenv: write error: Bad file descriptor", 2);
			}
		}
	}
	return (SUCCESS);
}
