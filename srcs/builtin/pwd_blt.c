/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_blt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 11:02:12 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 12:38:18 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		pwd_blt(char **av, t_list **lst)
{
	char	*pwd[2];

	(void)av;
	pwd[0] = "PWD";
	pwd[1] = NULL;
	printenv_blt(pwd, lst);
	return (SUCCESS);
}
