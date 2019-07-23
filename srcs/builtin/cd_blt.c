/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:45:13 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 12:34:06 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	set_pwd_oldpwd(char *curpath, char *buf, t_list **lst)
{
	char	*pwd[3];
	char	*oldpwd[3];

	put_name_val_in_tab("PWD", curpath, pwd);
	put_name_val_in_tab("OLDPWD", buf, oldpwd);
	setenv_blt(oldpwd, lst);
	setenv_blt(pwd, lst);
}

int			cd_blt(char **av, t_list **lst)
{
	char	*curpath;
	char	*pwd;

	av++;
	init_env(lst);
	pwd = ft_getenv("PWD", *lst);
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
	set_pwd_oldpwd(curpath, pwd, lst);
	if (ft_strequ(*av, "-") == TRUE)
		ft_putendl(curpath);
	ft_strdel(&curpath);
	return (SUCCESS);
}
