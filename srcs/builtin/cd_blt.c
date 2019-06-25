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
			return (FAILURE);
		}
		i++;
	}
	ft_strdel(&tmp_path);
	ft_free_tab(tab);
	return (SUCCESS);
}

int		cd_blt(char **av, t_list **lst)
{
	char	*path;
	char	buf[BUF_SIZE];

	getcwd(buf, BUF_SIZE);
	if (*av == NULL)
	{
		setenv_blt("PWD", getenv("HOME"), lst, 1);
		setenv_blt("OLDPWD", buf, lst, 1);
	}
	else if (ft_strequ(*av, "-") == TRUE)
	{
		setenv_blt("PWD", getenv("OLDPWD"), lst, 1);
		setenv_blt("OLDPWD", buf, lst, 1);
	}
	else
	{
		path = ft_asprintf("%s/%s", buf, *av);
		if (ft_check_path_access(path) == FAILURE)
			ft_putendl("cd: file not found");
		else
		{
			setenv_blt("PWD", path, lst, 1);
			setenv_blt("OLDPWD", buf, lst, 1);
		}
		ft_strdel(&path);
	}
	return (0);
}
