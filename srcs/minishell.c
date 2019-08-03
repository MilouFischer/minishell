/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:05:15 by efischer          #+#    #+#             */
/*   Updated: 2019/07/31 18:06:00 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t		pid;

int			exec_command(char **av, t_list **lst)
{
	int		ret;

	if (*av == NULL)
		return (SUCCESS);
	if (exec_builtin(av, &ret, lst) == FAILURE)
		ret = exec_bin(av, lst);
	return (ret);
}

static int	split_and_exec_command(char *buf, t_list **lst)
{
	char	**tab_operand;
	char	**av;
	size_t	i;
	int		ret;

	i = 0;
	av = NULL;
	ret = ft_atoi(ft_getenv("RET", *lst));
	tab_operand = ft_strsplit(buf, ';');
	ft_strdel(&buf);
	while (tab_operand[i] != NULL)
	{
		if (ft_get_command(&av, tab_operand[i], *lst) == FALSE)
		{
			ft_free_tab(av);
			ft_free_tab(tab_operand);
			ft_lstfree(*lst, free_env);
			return (FAILURE);
		}
		if (ft_strequ(*av, "exit") == TRUE)
			ft_free_tab(tab_operand);
		ret = exec_command(av, lst);
		ft_free_tab(av);
		i++;
	}
	ft_free_tab(tab_operand);
	return (ret);
}

static int	process_command(t_list **lst)
{
	char	*buf;
	int		ret;

	buf = NULL;
	if (get_next_line(0, &buf) == FAILURE)
	{
		ft_strdel(&buf);
		ft_putstr("minishell: error read input\n");
		return (FAILURE);
	}
	get_next_line(-42, NULL);
	if (buf == NULL)
		exit_blt(NULL, lst);
	if ((ret = split_and_exec_command(buf, lst)) != SUCCESS)
		return (ret);
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

static void	init_sig(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

int			main(int ac, char **av, char **envp)
{
	t_list	*lst;
	int		ret;

	(void)av;
	init_sig();
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
		ret = process_command(&lst);
		set_ret(ret, &lst);
	}
	return (EXIT_SUCCESS);
}
