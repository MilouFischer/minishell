/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 12:32:40 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 12:35:39 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

int			change_dir(char *curpath, char *dir_op, t_list **lst)
{
	int		ret;

	if ((ret = check_pathmax(&curpath, dir_op, *lst)) == FAILURE)
		ft_putendl_fd("minishell: cd: pathname too long", 2);
	else if ((ret = check_access(curpath)) == FAILURE)
		ft_putendl_fd("minishell: cd: cannot access file", 2);
	else if ((ret = chdir(curpath)) == FAILURE)
		ft_putendl_fd("minishell: cd: cannot change working directory", 2);
	return (ret);
}
