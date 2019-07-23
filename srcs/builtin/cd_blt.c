/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:45:13 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 13:47:55 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int		ft_check_arg(char *arg)
{
	size_t	i;

	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'P')
		{
			ft_putendl_fd("minishell: cd: invalid option", 2);
			ft_putendl_fd("usage: cd [-P] [directory]", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static int	get_flags(char ***av, uint8_t *flags)
{
	while (**av != NULL && ***av == '-')
	{
		if ((**av)[1] == '\0')
			return (SUCCESS);
		if (ft_strequ(**av, "--") == TRUE)
		{
			(*av)++;
			return (SUCCESS);
		}
		else if (ft_check_arg(**av) == FALSE)
			return (FAILURE);
		else
			*flags |= FLAG_P;
		(*av)++;
	}
	return (SUCCESS);
}

static void	set_pwd_oldpwd(char *curpath, char *buf, t_list **lst, uint8_t flags)
{
	char	*pwd[3];
	char	*oldpwd[3];

	if ((flags & FLAG_P) == FLAG_P)
		getcwd(curpath, PATH_MAX);
	put_name_val_in_tab("PWD", curpath, pwd);
	put_name_val_in_tab("OLDPWD", buf, oldpwd);
	setenv_blt(oldpwd, lst);
	setenv_blt(pwd, lst);
}

int			cd_blt(char **av, t_list **lst)
{
	char	*curpath;
	char	*pwd;
	uint8_t	flags;

	av++;
	init_env(lst);
	pwd = ft_getenv("PWD", *lst);
	if (get_flags(&av, &flags) == FAILURE)
		return (FAILURE);
	if (ft_tablen(av) > 1)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
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
	set_pwd_oldpwd(curpath, pwd, lst, flags);
	if (ft_strequ(*av, "-") == TRUE)
		ft_putendl(curpath);
	ft_strdel(&curpath);
	return (SUCCESS);
}
