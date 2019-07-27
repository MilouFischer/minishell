/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_cd_blt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:00:42 by efischer          #+#    #+#             */
/*   Updated: 2019/07/27 13:02:19 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_check_arg(char *arg, uint8_t *flags)
{
	size_t	i;

	i = 1;
	while (arg[i] != '\0')
	{
		*flags = 0;
		if (arg[i] == 'P')
			*flags |= FLAG_P;
		else if (arg[i] == 'L')
			*flags |= FLAG_L;
		else
		{
			ft_putstr_fd("minishell: cd: -", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putendl_fd(": Invalid option", 2);
			ft_putendl_fd("usage: cd [-L|-P] [directory]", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int			flags_cd_blt(char ***av, uint8_t *flags)
{
	*flags = 0;
	while (**av != NULL && ***av == '-')
	{
		if ((**av)[1] == '\0')
			return (SUCCESS);
		if (ft_strequ(**av, "--") == TRUE)
		{
			(*av)++;
			return (SUCCESS);
		}
		else if (ft_check_arg(**av, flags) == FALSE)
			return (FAILURE);
		(*av)++;
	}
	return (SUCCESS);
}
