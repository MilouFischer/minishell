/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:45:13 by efischer          #+#    #+#             */
/*   Updated: 2019/07/12 13:16:01 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access(char *path)
{
	char	**tab;
	char	*tmp_path;
	size_t	i;

	i = 0;
	tab = NULL;
	tmp_path = NULL;
	if (path == NULL)
		return (FAILURE);
	tab = ft_strsplit(path, '/');
	if (tab == NULL)
		return (FAILURE);
	while (tab[i] != NULL)
	{
		tmp_path = ft_join_free(tmp_path, "/", 1);
		tmp_path = ft_join_free(tmp_path, tab[i], 1);
		if (access(tmp_path, F_OK | R_OK) != SUCCESS)
		{
			ft_strdel(&tmp_path);
			ft_free_tab(tab);
			ft_putendl_fd("cd: can not access file", 2);
			return (FAILURE);
		}
		i++;
	}
	ft_strdel(&tmp_path);
	ft_free_tab(tab);
	return (SUCCESS);
}

static int	check_pathmax(char **curpath, char *dir_op, t_list *lst)
{
	size_t	len_curpath;
	size_t	len_dir_op;
	char	*pwd;
	char	*relativ_curpath;
	char	*tmp;

	len_curpath = ft_strlen(*curpath);
	len_dir_op = ft_strlen(dir_op);
	pwd = ft_getenv("PWD", lst);
	if (len_curpath + 1 > PATH_MAX && len_dir_op + 1 < PATH_MAX)
	{
		relativ_curpath = ft_strstr(*curpath, pwd);
		if (relativ_curpath == NULL)
			return (FAILURE);
		tmp = *curpath;
		*curpath = ft_strdup(relativ_curpath);
		ft_strdel(&tmp);
		if (ft_strlen(*curpath) + 1 > PATH_MAX)
			return (FALSE);
	}
	return (SUCCESS);
}

static void	fill_index_tab(int **index_tab, char **tab, ssize_t i)
{
	size_t	dot_count;

	dot_count = 0;
	while (i > 0)
	{
		i--;
		if (ft_strequ(tab[i], ".") == TRUE)
			(*index_tab)[i] = 0;
		else if (ft_strequ(tab[i], "..") == TRUE)
		{
			(*index_tab)[i] = 0;
			dot_count++;
		}
		else if (dot_count > 0)
		{
			(*index_tab)[i] = 0;
			dot_count--;
		}
		else
			(*index_tab)[i] = 1;
	}
}

static int	*get_index_tab(char **tab)
{
	int		*index_tab;
	ssize_t	i;
	ssize_t	tmp;

	i = 0;
	tmp = 0;
	while (tab[i] != NULL)
		i++;
	index_tab = (int*)malloc(sizeof(int) * i);
	ft_bzero(index_tab, i);
	fill_index_tab(&index_tab, tab, i);
	return (index_tab);
}

static void	get_clean_path(char **path)
{
	char	**tab;
	char	*clean_path;
	int		*index_tab;
	size_t	i;

	i = 0;
	clean_path = NULL;
	tab = ft_strsplit(*path, '/');
	index_tab = get_index_tab(tab);
	while (tab[i] != NULL)
	{
		if (index_tab[i] > 0)
		{
			clean_path = ft_join_free(clean_path, "/", 1);
			clean_path = ft_join_free(clean_path, tab[i], 1);
		}
		i++;
	}
	ft_strdel(path);
	*path = ft_strdup(clean_path);
	ft_strdel(&clean_path);
	ft_free_tab(tab);
	free(index_tab);
}

static char	*find_pathname(char *dir_op, char **pathname)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (pathname[i] != NULL)
	{
		len = ft_strlen(pathname[i]);
		if (pathname[i][len] != '/')
			pathname[i] = ft_join_free(pathname[i], "/", 1);
		pathname[i] = ft_join_free(pathname[i], dir_op, 1);
		if (access(pathname[i], F_OK | R_OK) == SUCCESS)
			return (pathname[i]);
		i++;
	}
	dir_op = ft_strjoin("./", dir_op);
	if (access(dir_op, F_OK | R_OK) == SUCCESS)
		return(dir_op);
	return (NULL);
}

static char	*check_cdpath(char *dir_op, t_list *lst)
{
	char	**pathname;
	char	*cdpath;

	cdpath = ft_getenv("CDPATH", lst);
	if (cdpath == NULL)
		return (NULL);
	pathname = ft_strsplit(cdpath, ':');
	return (find_pathname(dir_op, pathname));
}

int		cd_blt(char **av, t_list **lst)
{
	char	*curpath;
	char	buf[PATH_MAX];
	char	*tmp;
	char	*pwd;
	size_t	len;

	getcwd(buf, PATH_MAX);
	if (*av == NULL && ft_getenv("HOME", *lst) == NULL)
		return (FAILURE);
	else if (*av == NULL && ft_getenv("HOME", *lst) != NULL)
		curpath = ft_strdup(ft_getenv("HOME", *lst));
	else if (*av != NULL && *av[0] == '/')
		curpath = ft_strdup(*av);
	else if (ft_strequ(*av, ".") || ft_strequ(*av, ".."))
		curpath = ft_strdup(*av);
	else if ((tmp = check_cdpath(*av, *lst)) != NULL)
	{
		curpath = tmp;
		ft_strdel(&tmp);
	}
	else
		curpath = ft_strdup(*av);
	/*Jump this step if -P option is enable*/
	pwd = ft_strdup(ft_getenv("PWD", *lst));
	if (curpath[0] != '/' && pwd != NULL)
	{
		len = ft_strlen(pwd);
		if (pwd[len] != '/')
			pwd = ft_join_free(pwd, "/", 1);
		curpath = ft_join_free(pwd, curpath, 3);
	}
	get_clean_path(&curpath);
	if (check_pathmax(&curpath, *av, *lst) == FAILURE)
		return (FAILURE);
	if (check_access(curpath) == FAILURE)
		return (FAILURE);
	if (chdir(curpath) == FAILURE)
		return (FAILURE);
	setenv_blt("PWD", curpath, lst, 1);
	setenv_blt("OLDPWD", buf, lst, 1);
	ft_strdel(&curpath);
	return (SUCCESS);
}
