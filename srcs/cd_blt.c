/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:00:28 by efischer          #+#    #+#             */
/*   Updated: 2019/06/15 13:34:22 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_flags(char ***av, uint8_t *flags)
{
	(void)flags;
	while (***av == '-')
		(*av)++;
}

int		cd_blt(char **av)
{
	uint8_t	flags;
	char	*path;
	char	buf[BUF_SIZE];

	flags = 0;
	if (*av != NULL && *av[0] == '-')
		ft_check_flags(&av, &flags);
	if (*av == '\0')
		chdir(getenv("HOME"));
	else
	{
		getcwd(buf, BUF_SIZE);
		path = ft_asprintf("%s/%s", buf, *av);
//		ft_check_path_access(path);
		chdir(path);
		ft_strdel(&path);
	}
	return (0);
}
