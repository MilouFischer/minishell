/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:30:17 by efischer          #+#    #+#             */
/*   Updated: 2019/08/08 14:47:54 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char *av, t_list *lst)
{
	char		**path_tab;
	char		*path;
	struct stat	buf;
	size_t		i;

	i = 0;
	if ((path = ft_getenv("PATH", lst)) == NULL)
		return (NULL);
	path_tab = ft_strsplit(path, ':');
	ft_strdel(&path);
	if (path_tab == NULL)
		return (NULL);
	while (path_tab[i] != NULL)
	{
		path = ft_asprintf("%s/%s", path_tab[i], av);
		if (lstat(path, &buf) != FAILURE)
			break ;
		ft_strdel(&path);
		i++;
	}
	ft_free_tab(path_tab);
	return (path);
}

static int	check_path(char *path, char *av)
{
	struct stat	buf;

	if (lstat(path, &buf) == FAILURE)
	{
		if (av[0] != '/' && ft_strnequ(av, "./", 2) == FALSE)
			ft_dprintf(2, "minishell: command not found: %s\n", av);
		else
			ft_dprintf(2, "minishell: %s: No such file or directory\n", av);
	}
	else if ((buf.st_mode & S_IFDIR) == S_IFDIR)
		ft_dprintf(2, "minishell: %s: Is a directory\n", av);
	else if ((buf.st_mode & S_IFREG) == S_IFREG
			&& (buf.st_mode & S_IXUSR) != S_IXUSR)
		ft_dprintf(2, "minishell: %s: Permission denied\n", av);
	else
		return (SUCCESS);
	return (FAILURE);
}

static int	exec(t_list *lst, char **av)
{
	char	*path;
	char	**env;

	env = ft_lst_to_char_tab(lst, get_content_to_tab);
	if (av[0][0] != '/' && ft_strnequ(av[0], "./", 2) == FALSE)
		path = find_path(*av, lst);
	else
		path = av[0];
	if (check_path(path, *av) == SUCCESS)
		execve(path, av, env);
	ft_strdel(&path);
	ft_free_tab(env);
	return (ERROR);
}

static int	interrupted_exec(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGSEGV)
			ft_putendl_fd("\nsegmentation fault", 2);
		else if (WTERMSIG(status) == SIGABRT)
			ft_putendl_fd("\nabort", 2);
		else if (WTERMSIG(status) == SIGILL)
			ft_putendl_fd("\nillegal option", 2);
		else if (WTERMSIG(status) == SIGFPE)
			ft_putendl_fd("\nfloating point exception", 2);
		else if (WTERMSIG(status) == SIGPIPE)
			ft_putendl_fd("broken pipe", 2);
		else if (WTERMSIG(status) == SIGALRM)
			ft_putendl_fd("\nalert signal", 2);
		else if (WTERMSIG(status) == SIGTERM)
			ft_putendl_fd("\ncomplet", 2);
		else if (WTERMSIG(status) == SIGKILL)
			ft_putendl_fd("\nkilled", 2);
		return (WTERMSIG(status) + 128);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (FALSE);
}

int			exec_bin(char **av, t_list **lst)
{
	int		status;
	int		ret;
	int		cur_pid;

	status = 0;
	g_pid = fork();
	if (g_pid == FAILURE)
		return (FAILURE);
	else if (g_pid == 0)
	{
		if (exec(*lst, av) == ERROR)
			exit(ERROR);
	}
	else if (g_pid > 0)
	{
		cur_pid = g_pid;
		if (waitpid(cur_pid, &status, WUNTRACED) != 0)
		{
			if ((ret = interrupted_exec(status)) != FALSE)
				return (ret);
		}
		return (SUCCESS);
	}
	return (FAILURE);
}
