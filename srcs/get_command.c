/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 11:56:37 by efischer          #+#    #+#             */
/*   Updated: 2019/07/30 13:56:11 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_tabulation(char **av)
{
	size_t	i;
	char	**tab;

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

int			ft_get_command(char ***av, t_list *lst)
{
	char *buf;

	buf = NULL;
	if (get_next_line(0, &buf) == FAILURE)
	{
		ft_strdel(&buf);
		ft_putstr("minishell: error read input\n");
		return (FALSE);
	}
	get_next_line(-42, NULL);
	*av = ft_strsplit(buf, ' ');
	remove_tabulation(*av);
	ft_strdel(&buf);
	if (*av == NULL)
		exit_blt(*av, &lst);
	check_expansion(*av, lst);
	return (TRUE);
}
