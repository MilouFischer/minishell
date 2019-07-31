/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 11:56:37 by efischer          #+#    #+#             */
/*   Updated: 2019/07/31 15:27:33 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_tabulation(char **av)
{
	size_t	i;
	char	**tab;

	if (av == NULL)
		return ;
	while (*av != NULL)
	{
		i = 0;
		tab = ft_strsplit(*av, '	');
		ft_strdel(av);
		while (tab[i] != NULL)
		{
			*av = ft_join_free(*av, tab[i], 1);
			i++;
		}
		ft_free_tab(tab);
		av++;
	}
}

static void	check_expansion(char **av, t_list *lst)
{
	size_t	i;

	i = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '~')
			process_tilde(&av[i], lst);
		if (ft_strchr(av[i], '$') != NULL)
			process_dollar(&av[i], lst);
		i++;
	}
}

int			ft_get_command(char ***av, char *buf, t_list *lst)
{
	*av = ft_strsplit(buf, ' ');
	remove_tabulation(*av);
	if (*av == NULL)
		exit_blt(*av, &lst);
	check_expansion(*av, lst);
	return (TRUE);
}
