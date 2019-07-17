/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:45:13 by efischer          #+#    #+#             */
/*   Updated: 2019/07/12 16:47:12 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_each_file(char **tab)
{
	char	*tmp_path;
	size_t	i;

	i = 0;
	tmp_path = NULL;
	while (tab[i] != NULL)
	{
		tmp_path = ft_join_free(tmp_path, "/", 1);
		tmp_path = ft_join_free(tmp_path, tab[i], 1);
		if (access(tmp_path, F_OK | R_OK) != SUCCESS)
		{
			ft_strdel(&tmp_path);
			ft_free_tab(tab);
			return (FAILURE);
		}
		i++;
	}
	ft_strdel(&tmp_path);
	return (SUCCESS);
}

static int	check_access(char *path)
{
	char	**tab;

	tab = NULL;
	if (path == NULL)
		return (FAILURE);
	tab = ft_strsplit(path, '/');
	if (tab == NULL)
		return (FAILURE);
	if (check_each_file(tab) == FAILURE)
		return (FAILURE);
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

	i = 0;
	while (tab[i] != NULL)
		i++;
	index_tab = (int*)malloc(sizeof(int) * i);
	ft_bzero(index_tab, i);
	fill_index_tab(&index_tab, tab, i);
	return (index_tab);
}

static char	*path_cleaning(char *path)
{
	char	**tab;
	char	*clean_path;
	int		*index_tab;
	size_t	i;

	i = 0;
	clean_path = NULL;
	tab = ft_strsplit(path, '/');
	if (tab == NULL)
		return (NULL);
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
	if (clean_path == NULL)
		clean_path = ft_join_free(clean_path, "/", 1);
	ft_free_tab(tab);
	free(index_tab);
	return (clean_path);
}

static void	get_clean_path(char **path)
{
	char	*clean_path;

	clean_path = NULL;
	if (path == NULL || *path == NULL)
		return ;
	clean_path = path_cleaning(*path);
	ft_strdel(path);
	*path = ft_strdup(clean_path);
	ft_strdel(&clean_path);
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
	char	*curpath;

	cdpath = ft_getenv("CDPATH", lst);
	if (cdpath == NULL)
		return (NULL);
	pathname = ft_strsplit(cdpath, ':');
	curpath = find_pathname(dir_op, pathname);
	ft_free_tab(pathname);
	return (curpath);
}

static char	*get_special_path(char *dir_op, t_list *lst)
{
	char	*curpath;
	char	*tmp;

	curpath = NULL;
	if (dir_op == NULL && ft_getenv("HOME", lst) == NULL)
		return (NULL);
	else if (dir_op == NULL && ft_getenv("HOME", lst) != NULL)
		curpath = ft_strdup(ft_getenv("HOME", lst));
	else if (ft_strequ(dir_op, "-") == TRUE)
		curpath = ft_strdup(ft_getenv("OLDPWD", lst));
	else if (dir_op != NULL && dir_op[0] == '/')
		curpath = ft_strdup(dir_op);
	else if (ft_strequ(dir_op, ".") || ft_strequ(dir_op, ".."))
		curpath = ft_strdup(dir_op);
	else if ((tmp = check_cdpath(dir_op, lst)) != NULL)
	{
		curpath = tmp;
		ft_strdel(&tmp);
	}
	return (curpath);
}

static char	*get_path(char *dir_op, t_list *lst)
{
	char	*curpath;
	char	*pwd;
	size_t	len;

	curpath = get_special_path(dir_op, lst);
	if (curpath == NULL && dir_op != NULL)
		curpath = ft_strdup(dir_op);
	else if (curpath == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (NULL);
	}
	pwd = ft_strdup(ft_getenv("PWD", lst));
	if (curpath[0] != '/' && pwd != NULL)
	{
		len = ft_strlen(pwd);
		if (pwd[len] != '/')
			pwd = ft_join_free(pwd, "/", 1);
		curpath = ft_join_free(pwd, curpath, 2);
	}
	ft_strdel(&pwd);
	return (curpath);
}

static int	change_dir(char *curpath, char *dir_op, t_list **lst)
{
	if (check_pathmax(&curpath, dir_op, *lst) == FAILURE)
	{
		ft_putendl_fd("./minishell: cd: pathname too long", 2);
		return (FAILURE);
	}
	if (check_access(curpath) == FAILURE)
	{
		ft_putendl_fd("./minishell: cd: cannot access file", 2);
		return (FAILURE);
	}
	if (chdir(curpath) == FAILURE)
	{
		ft_putendl_fd("./minishell: cd: cannot change working directory", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	set_pwd_oldpwd(char *curpath, char *buf, t_list **lst)
{
	char	*pwd[3];
	char	*oldpwd[3];

	pwd[0] = "PWD";
	pwd[1] = curpath;
	pwd[2] = NULL;
	oldpwd[0] = "OLDPWD";
	oldpwd[1] = buf;
	oldpwd[2] = NULL;
	setenv_blt(pwd, lst);
	setenv_blt(oldpwd, lst);
}

int			cd_blt(char **av, t_list **lst)
{
	char	*curpath;
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	if (ft_tablen(av) > 1)
	{
		ft_putendl_fd("./minishell: cd: too many arguments", 2);
		return (FAILURE);
	}
	curpath = get_path(*av, *lst);
	get_clean_path(&curpath);
	if (curpath == NULL)
		return (FAILURE);
	if (change_dir(curpath, *av, lst) == FAILURE)
	{
		ft_strdel(&curpath);
		return (FAILURE);
	}
	set_pwd_oldpwd(curpath, buf, lst);
	if (ft_strequ(*av, "-") == TRUE)
		ft_putendl(curpath);
	ft_strdel(&curpath);
	return (SUCCESS);
}
