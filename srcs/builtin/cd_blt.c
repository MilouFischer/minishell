/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:00:28 by efischer          #+#    #+#             */
/*   Updated: 2019/06/18 13:15:20 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	ft_check_flags(char ***av, uint8_t *flags)
{
	(void)flags;
	while (**av[0] == '-' && ft_strlen(**av) > 1)
	{
		(*av)++;
	}
}*/

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

static void	clean_path(char **path)
{
	char	**tab;
	char	*clean_path;
	size_t	i;

	i = 0;
	clean_path = NULL;
	tab = ft_strsplit(*path, '/');
	while (tab[i] != NULL)
	{
		if (ft_strequ(tab[i], ".") == FALSE && ft_strequ(tab[i], "..") == FALSE
			&& ft_strequ(tab[i + 1], "..") == FALSE)
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
}

static char	*get_path(char **av, t_list *lst)
{
	char	*path;
	char	*pwd;

	path = NULL;
	if (*av == NULL && ft_getenv("HOME", lst) == NULL)
		return (NULL);
	if (*av == NULL)
		path = ft_strdup(ft_getenv("HOME", lst));
	else if (ft_strequ(av[0], "-") == TRUE)
		path = ft_strdup(ft_getenv("OLDPWD", lst));
	else if (av[0][0] == '/')
		path = ft_strdup(av[0]);
	else
	{
		pwd = ft_strdup(ft_getenv("PWD", lst));
		if (pwd[ft_strlen(pwd)] != '/')
			pwd = ft_join_free(pwd, "/", 1);
		path = ft_join_free(pwd, av[0], 1);
	}
	return (path);
}

int			cd_blt(char **av, t_list **lst)
{
	char	*path;
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	path = get_path(av, *lst);
	if (path == NULL)
		return (FAILURE);
	clean_path(&path);
	if (check_access(path) == FAILURE)
	{
		ft_putendl_fd("access fail", 2);
		return (FAILURE);
	}
	if (chdir(path) == FAILURE)
	{
		ft_putendl_fd("chdir fail", 2);
		return (FAILURE);
	}
	setenv_blt("PWD", path, lst, 1);
	setenv_blt("OLDPWD", buf, lst, 1);
	ft_strdel(&path);
	return (SUCCESS);
}
