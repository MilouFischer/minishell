/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:30:17 by efischer          #+#    #+#             */
/*   Updated: 2019/07/24 13:55:10 by efischer         ###   ########.fr       */
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
		if (execve(path, av, env) != FAILURE)
		{
			ft_strdel(&path);
			return (SUCCESS);
		}
	}
	else
	{
		if (exec_path(lst, av, env) == SUCCESS)
			return (SUCCESS);
	}
	return (FAILURE);
}

int			exec_bin(char **av, t_list **lst)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == FAILURE)
		return (FAILURE);
	if (pid > 0)
	{
		if (waitpid(pid, &status, WUNTRACED) > 0)
		{
			if (WIFSIGNALED(status))
			{
				ft_putchar_fd('\n', 2);
				return (WEXITSTATUS(status));
			}
		}
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (exec(*lst, av) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
