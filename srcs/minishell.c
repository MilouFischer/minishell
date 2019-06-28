/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:05:15 by efischer          #+#    #+#             */
/*   Updated: 2019/06/18 15:22:22 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec(t_list *lst, char **av)
{
	char	**path_tab;
	char	**env;
	char	*path;
	size_t	i;

	i = 0;
	path = NULL;
	env = ft_lst_to_char_tab(lst, get_content_to_tab);
	while (lst != NULL
	&& ft_strequ(((t_env*)(lst->content))->name, "PATH") == FALSE)
		lst = lst->next;
	if (lst == NULL)
		return (FAILURE);
	path_tab = ft_strsplit(((t_env*)(lst->content))->value, ':');
	while (path_tab[i] != NULL)
	{
		path = ft_asprintf("%s/%s", path_tab[i], av[0]);
		if (execve(path, av, env) != FAILURE)
		{
			ft_strdel(&path);
			return (SUCCESS);
		}
		ft_strdel(&path);
		i++;
	}
	return (FAILURE);
}

static int	ft_exec_bin(char **av, t_list **lst)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == FAILURE)
		return (FAILURE);
	if (pid > 0)
		wait(&status);
	if (pid == 0)
	{
		if (exec(*lst, av) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	ft_exec_builtin(char **av, t_list **lst)
{
	int		status;

	status = 0;
	if (ft_strequ(av[0], "exit") == TRUE)
	{
		if (av[1] != NULL)
			status = ft_atoi(av[1]);
		ft_free_tab(av);
		exit_blt(status, *lst);
	}
	else if (ft_strequ(av[0], "echo") == TRUE)
		echo_blt(av + 1);
	else if (ft_strequ(av[0], "cd") == TRUE)
		cd_blt(av + 1, lst);
	else if (ft_strequ(av[0], "env") == TRUE)
		env_blt(av + 1, *lst);
	else if (ft_strequ(av[0], "printenv") == TRUE)
		printenv_blt(av + 1, *lst);
	else if (ft_strequ(av[0], "pwd") == TRUE)
		pwd_blt(*lst);
	else if (ft_strequ(av[0], "unsetenv") == TRUE)
	{
		if (unsetenv_blt(av[1], lst) == FAILURE)
			ft_putstr_fd("unsetenv fail", 2);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int			exec_command(char **av, t_list **lst)
{
	if (*av == NULL)
		return (SUCCESS);
	if (ft_exec_builtin(av, lst) == FAILURE)
	{
		if (ft_exec_bin(av, lst) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	process_command(t_list **lst)
{
	char	**tab;
	char	*error;

	tab = NULL;
	if (ft_get_command(&tab) == FALSE)
	{
		ft_free_tab(tab);
		return (FAILURE);
	}
	if (exec_command(tab, lst) == FAILURE)
	{
		error = ft_asprintf("minishell: command not found: %s\n", tab[0]);
		ft_putstr_fd(error, 2);
		ft_strdel(&error);
		ft_free_tab(tab);
		exit_blt(EXIT_FAILURE, *lst);
	}
	ft_free_tab(tab);
	return (SUCCESS);
}

int			main(int ac, char **av, char **envp)
{
	t_list	*lst;

	(void)ac;
	(void)av;
	lst = NULL;
	ft_bzero(&lst, sizeof(lst));
	get_env_lst(envp, &lst);
	while (1)
	{
		ft_putstr("$> ");
		if (process_command(&lst) == FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
