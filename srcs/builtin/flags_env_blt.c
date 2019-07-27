/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_env_blt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 12:50:56 by efischer          #+#    #+#             */
/*   Updated: 2019/07/27 12:52:12 by efischer         ###   ########.fr       */
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
		if (arg[i] == 'i')
			*flags |= FLAG_I;
		else
		{
			ft_putstr_fd("minishell: env: -", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putendl_fd(": Invalid option", 2);
			ft_putstr_fd("usage: env [-i] [name=value]...", 2);
			ft_putendl_fd("[utility [argument...]]", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int			flags_env_blt(char ***av, uint8_t *flags)
{
	*flags = 0;
	while (**av != NULL && ***av == '-')
	{
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
