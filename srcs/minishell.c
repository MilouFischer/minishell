/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:05:15 by efischer          #+#    #+#             */
/*   Updated: 2019/08/05 17:01:27 by efischer         ###   ########.fr       */
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

void		keep_tab(char **tab_operand, uint8_t opt)
{
	static char **tab_cp;

	if (opt == INIT_TAB)
		tab_cp = tab_operand;
	else
		ft_free_tab(tab_cp);
}

static int	check_follow(char *str)
{
	char	**tab;
	size_t	i;

	i = 0;
	if (ft_strchr(str, ';') == NULL)
		return (TRUE);
	else if (str != NULL && (str[0] == ';' || ft_strstr(str, ";;") != NULL))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return (FALSE);
	}
	tab = ft_strsplit(str, ';');
	while (tab[i] != NULL)
	{
		if (ft_str_is_blank(tab[i]) == TRUE)
		{
			ft_free_tab(tab);
			ft_putendl_fd("minishell: syntax error", 2);
			return (FALSE);
		}
		i++;
	}
	ft_free_tab(tab);
	return (TRUE);
}

static int	split_and_exec_command(char *buf, t_list **lst)
{
	char	**tab_operand;
	char	**av;
	size_t	i;
	int		ret;

	i = 0;
	av = NULL;
	ret = g_ret;
	if (check_follow(buf) == FALSE)
	{
		ft_strdel(&buf);
		return (2);
	}
	tab_operand = ft_strsplit(buf, ';');
	keep_tab(tab_operand, INIT_TAB);
	ft_strdel(&buf);
	while (tab_operand[i] != NULL)
	{
		if (ft_get_command(&av, tab_operand[i], *lst) == FALSE)
		{
			ft_free_tab(av);
			ft_free_tab(tab_operand);
			return (ret);
		}
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

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_pid == 0)
		{
			ft_putstr_fd("\n$> ", 2);
			g_ret = 127;
		}
		else
			ft_putstr_fd("\n", 2);
	}
	g_pid = 0;
}

static void	init_sig(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
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
