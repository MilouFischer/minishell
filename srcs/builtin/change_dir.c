/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 12:32:40 by efischer          #+#    #+#             */
/*   Updated: 2019/07/31 18:42:10 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	put_error(char *err_str, char *path, int error, t_list *lst)
{
	ft_putstr_fd(err_str, 2);
	if (ft_strequ(path, "-") == TRUE && ft_getenv("OLDPWD", lst) == NULL)
	{
		ft_putendl_fd("OLDPWD not set", 2);
		return ;
	}
	if (ft_strequ(path, "-") == TRUE)
		path = ft_getenv("OLDPWD", lst);
	if (path == NULL)
		path = ft_getenv("HOME", lst);
	ft_putstr_fd(path, 2);
	if (error == NOTFOUND)
		ft_putendl_fd(": No such file or directory", 2);
	else if (error == NOPERM)
		ft_putendl_fd(": Permission denied", 2);
	else if (error == NODIR)
		ft_putendl_fd(": Not a directory", 2);
	else if (error == EPATH)
		ft_putendl_fd(": Path too long", 2);
}

static int	check_each_file(char **tab, int *error)
{
	char	*tmp_path;
	size_t	i;

	i = 0;
	tmp_path = NULL;
	while (tab[i] != NULL)
	{
		tmp_path = ft_join_free(tmp_path, "/", 1);
		tmp_path = ft_join_free(tmp_path, tab[i], 1);
		if (access(tmp_path, F_OK) != SUCCESS)
			*error = NOTFOUND;
		else if (access(tmp_path, R_OK) != SUCCESS)
			*error = NOPERM;
		if (*error != 0)
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

static int	check_access(char *path, int *error)
{
	char	**tab;

	tab = NULL;
	if (path == NULL)
		return (FAILURE);
	tab = ft_strsplit(path, '/');
	if (tab == NULL)
		return (FAILURE);
	if (check_each_file(tab, error) != SUCCESS)
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

int			change_dir(char *curpath, char *dir_op, t_list **lst)
{
	int		ret;
	int		error;

	error = 0;
	if ((ret = check_pathmax(&curpath, dir_op, *lst)) == FAILURE)
		put_error("minishell: cd: ", dir_op, EPATH, *lst);
	else if ((ret = check_access(curpath, &error)) == FAILURE)
		put_error("minishell: cd: ", dir_op, error, *lst);
	else if ((ret = chdir(curpath)) == FAILURE)
		put_error("minishell: cd: ", dir_op, NODIR, *lst);
	return (ret);
}
