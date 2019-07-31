/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:05:15 by efischer          #+#    #+#             */
/*   Updated: 2019/07/31 15:27:13 by efischer         ###   ########.fr       */
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
	char	**av;
	size_t	i;
	char	*buf;
	char	**tab_operand;

	i = 0;
	av = NULL;
	buf = NULL;
	if (get_next_line(0, &buf) == FAILURE)
	{
		ft_strdel(&buf);
		ft_putstr("minishell: error read input\n");
		return (FAILURE);
	}
	get_next_line(-42, NULL);
	tab_operand = ft_strsplit(buf, ';');
	while (tab_operand[i] != NULL)
	{
		if (ft_get_command(&av, tab_operand[i], *lst) == FALSE)
		{
			ft_free_tab(av);
			ft_lstfree(*lst, free_env);
			return (FAILURE);
		}
		if (exec_command(av, lst) != SUCCESS)
		{
			ft_free_tab(av);
			return (FAILURE);
		}
		ft_free_tab(av);
		i++;
	}
	ft_free_tab(tab_operand);
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
