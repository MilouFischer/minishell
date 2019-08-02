/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:30:17 by efischer          #+#    #+#             */
/*   Updated: 2019/07/31 18:15:59 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_path(t_list *lst, char **av, char **env)
{
	char	**path_tab;
	char	*path;
	size_t	i;

	i = 0;
	path = NULL;
	while (lst != NULL
	&& ft_strequ(((t_env*)(lst->content))->name, "PATH") == FALSE)
		lst = lst->next;
	if (lst == NULL)
		return (FAILURE);
	path_tab = ft_strsplit(((t_env*)(lst->content))->value, ':');
	if (path_tab == NULL)
		return (FAILURE);
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

static int	exec(t_list *lst, char **av)
{
	char	**env;
	char	*path;

	env = ft_lst_to_char_tab(lst, get_content_to_tab);
	if (av[0][0] == '/' || ft_strnequ(av[0], "./", 2) == TRUE)
	{
		path = av[0];
		execve(path, av, env);
		ft_strdel(&path);
	}
	else
		exec_path(lst, av, env);
	ft_dprintf(2, "minishell: command not found: %s\n", av[0]);
	return (FAILURE);
}

static int	interrupted_exec(int status)
{
	int		ret;

	if (WIFSIGNALED(status))
	{
		ret = WTERMSIG(status);
		if (ret == SIGSEGV)
			ft_putendl_fd("\nsegmentation fault", 2);
		if (ret == SIGABRT)
			ft_putendl_fd("\nabort", 2);
		if (ret == SIGILL)
			ft_putendl_fd("\nillegal option", 2);
		if (ret == SIGFPE)
			ft_putendl_fd("\nfloating point exception", 2);
		if (ret == SIGPIPE)
			ft_putendl_fd("", 2);
		if (ret == SIGALRM)
			ft_putendl_fd("\nalert signal", 2);
		if (ret == SIGTERM)
			ft_putendl_fd("\ncomplet", 2);
		if (ret == SIGKILL)
			ft_putendl_fd("\nkilled", 2);
		return (ret);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (FALSE);
}

int			exec_bin(char **av, t_list **lst)
{
	int		status;
	int		ret;

	status = 0;
	pid = fork();
	if (pid == FAILURE)
		return (FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (exec(*lst, av) == FAILURE)
			return (FAILURE);
	}
	else if (pid > 0)
	{
		if (waitpid(pid, &status, WUNTRACED) == pid)
		{
			if ((ret = interrupted_exec(status)) != FALSE)
				return (ret);
		}
		return (SUCCESS);
	}
	return (SUCCESS);
}
