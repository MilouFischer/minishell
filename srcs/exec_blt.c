/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:33:17 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 11:28:36 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_builtin(char **av, t_list **lst)
{
	static const char	*builtin[NB_OF_BLT] = { BUILTIN };
	static int			(*f_blt[NB_OF_BLT])(char **, t_list **) = { CD_BLT,
						EXIT_BLT, PWD_BLT, ECHO_BLT, ENV_BLT, SETENV_BLT,
						UNSETENV_BLT, PRINTENV_BLT };
	size_t				i;

	i = 0;
	while (i < NB_OF_BLT)
	{
		if (ft_strequ(av[0], builtin[i]) == TRUE)
		{
			f_blt[i](av, lst);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}
