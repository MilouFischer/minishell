/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:54:23 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 12:41:46 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
		return (dir_op);
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

char		*get_path(char *dir_op, t_list *lst)
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
