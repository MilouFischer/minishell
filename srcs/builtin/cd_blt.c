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

static int	ft_check_path_access(char *path)
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
			ft_putendl_fd("cd: permission denied", 2);
			return (FAILURE);
		}
		i++;
	}
	ft_strdel(&tmp_path);
	ft_free_tab(tab);
	return (SUCCESS);
}

static int	check_dot(char *arg)
{
	if (arg == NULL)
		return (FALSE);
	if (arg[0] == '.')
	{
		if (arg[1] == '\0' || arg[1] == '/')
			return (TRUE);
		if (arg[1] == '.')
		{
			if (arg[2] == '\0' || arg[2] == '/')
				return (TRUE);
		}
	}
	return (FALSE);
}

static char	*ft_getenv(char *env_name, t_list *lst)
{
	if (env_name == NULL || lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (ft_strequ(((t_env*)(lst->content))->name, env_name) == TRUE)
			return (((t_env*)(lst->content))->value);
		lst = lst->next;
	}
	return (NULL);
}

int			cd_blt(char **av, t_list **lst)
{
	char	*path;
	char	*pwd;
	char	buf[BUF_SIZE];

	path = NULL;
	if (*av == NULL && ft_getenv("HOME", *lst) == NULL)
		return (FAILURE);
	getcwd(buf, BUF_SIZE);
	if (*av == NULL)
		path = ft_strdup(ft_getenv("HOME", *lst));
	else if (av[0][0] == '/')
		path = ft_strdup(av[0]);
	else if (ft_strequ(av[0], "-") == TRUE)
		path = ft_strdup(ft_getenv("OLDPWD", *lst));
	else if (check_dot(av[0]) == TRUE)
	{
		if (ft_check_path_access(av[0]) == FAILURE)
			return (FAILURE);
		if (chdir(av[0]) == FAILURE)
		{
			ft_putendl_fd("cd: file not found", 2);
			return (FAILURE);
		}
		setenv_blt("PWD", av[0], lst, 1);
		setenv_blt("OLDPWD", buf, lst, 1);
	}
	else
	{
		pwd = ft_strdup(ft_getenv("PWD", *lst));
		if (pwd[ft_strlen(pwd)] != '/')
			pwd = ft_join_free(pwd, "/", 1);
		path = ft_join_free(pwd, av[0], 1);
	}
	if (path != NULL)
	{
		if (ft_check_path_access(path) == FAILURE)
			return (FAILURE);
		if (chdir(path) == FAILURE)
		{
			ft_putendl_fd("cd: file not found", 2);
			return (FAILURE);
		}
		setenv_blt("PWD", path, lst, 1);
		setenv_blt("OLDPWD", buf, lst, 1);
	}
	ft_strdel(&path);
	return (SUCCESS);
}
