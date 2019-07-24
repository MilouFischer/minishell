/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:05:15 by efischer          #+#    #+#             */
/*   Updated: 2019/07/24 14:09:30 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_command(char **av, t_list **lst)
{
	if (*av == NULL)
		return (SUCCESS);
	if (exec_builtin(av, lst) == FAILURE)
	{
		if (exec_bin(av, lst) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	process_command(t_list **lst)
{
	char	**tab;
	char	*error;

	tab = NULL;
	if (ft_get_command(&tab, *lst) == FALSE)
	{
		ft_free_tab(tab);
		return (FAILURE);
	}
	if (exec_command(tab, lst) == FAILURE)
	{
		error = ft_asprintf("minishell: command not found: %s\n", tab[0]);
		ft_putstr_fd(error, 2);
		ft_strdel(&error);
		exit(EXIT_FAILURE);
	}
	ft_free_tab(tab);
	return (SUCCESS);
}

int			main(int ac, char **av, char **envp)
{
	t_list	*lst;

	(void)av;
	if (ac >= 2)
	{
		ft_putendl_fd("minishell: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	lst = NULL;
	ft_bzero(&lst, sizeof(lst));
	get_env_lst(envp, &lst);
	init_env(&lst);
	while (1)
	{
		ft_putstr_fd("$> ", 2);
		signal(SIGINT, SIG_IGN);
		if (process_command(&lst) == FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
