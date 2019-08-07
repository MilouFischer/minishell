/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:05:15 by efischer          #+#    #+#             */
/*   Updated: 2019/08/07 16:39:03 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t		g_pid;
int			g_ret;

int			exec_command(char **av, t_list **lst)
{
	int		ret;

	if (*av == NULL)
		return (SUCCESS);
	if (exec_builtin(av, &ret, lst) == FAILURE)
		ret = exec_bin(av, lst);
	return (ret);
}

static void	exec_each_operand(char **tab_operand, char **av, t_list **lst)
{
	size_t	i;

	i = 0;
	while (tab_operand[i] != NULL)
	{
		if (ft_get_command(&av, tab_operand[i], *lst) == FALSE)
		{
			ft_free_tab(av);
			i++;
			continue ;
		}
		g_ret = exec_command(av, lst);
		ft_free_tab(av);
		i++;
	}
}

static int	split_and_exec_command(char *buf, t_list **lst)
{
	char	**tab_operand;
	char	**av;

	av = NULL;
	if (check_follow(buf) == FALSE)
	{
		ft_strdel(&buf);
		return (2);
	}
	tab_operand = ft_strsplit(buf, ';');
	keep_tab(tab_operand, INIT_TAB);
	ft_strdel(&buf);
	exec_each_operand(tab_operand, av, lst);
	ft_free_tab(tab_operand);
	return (g_ret);
}

static int	process_command(t_list **lst)
{
	char	*buf;
	int		ret;

	buf = NULL;
	if (get_next_line(0, &buf) == FAILURE)
	{
		ft_strdel(&buf);
		ft_putendl_fd("minishell: error read input", 2);
		exit(EXIT_FAILURE);
	}
	get_next_line(-42, NULL);
	if (buf == NULL)
		exit_blt(NULL, lst);
	if ((ret = split_and_exec_command(buf, lst)) != SUCCESS)
		return (ret);
	return (SUCCESS);
}

int			main(int ac, char **av, char **envp)
{
	t_list	*lst;

	(void)av;
	init_sig();
	if (ac >= 2)
	{
		ft_putendl_fd("minishell: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	lst = NULL;
	keep_tab(NULL, INIT_TAB);
	ft_bzero(&lst, sizeof(lst));
	get_env_lst(envp, &lst);
	init_env(&lst);
	while (1)
	{
		g_pid = 0;
		ft_putstr_fd("$> ", 2);
		g_ret = process_command(&lst);
		keep_tab(NULL, INIT_TAB);
	}
	return (EXIT_SUCCESS);
}
