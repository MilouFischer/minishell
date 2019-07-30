/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:05:15 by efischer          #+#    #+#             */
/*   Updated: 2019/07/27 18:03:32 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t		pid;

int			exec_command(char **av, t_list **lst)
{
	if (*av == NULL)
		return (SUCCESS);
	if (exec_builtin(av, lst) == FAILURE)
		return (exec_bin(av, lst));
	return (SUCCESS);
}

static int	process_command(t_list **lst)
{
	char	**tab;

	tab = NULL;
	if (ft_get_command(&tab, *lst) == FALSE)
	{
		ft_free_tab(tab);
		ft_lstfree(*lst, free_env);
		return (FAILURE);
	}
	if (exec_command(tab, lst) != SUCCESS)
	{
		ft_free_tab(tab);
		return (FAILURE);
	}
	ft_free_tab(tab);
	return (SUCCESS);
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (pid == 0)
			ft_putstr_fd("\n$> ", 2);
		else
			ft_putstr_fd("\n", 2);
	}
	pid = 0;
}

int			main(int ac, char **av, char **envp)
{
	t_list	*lst;

	(void)av;
	signal(SIGINT, sigint_handler);
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
		pid = 0;
		ft_putstr_fd("$> ", 2);
		process_command(&lst);
	}
	return (EXIT_SUCCESS);
}
