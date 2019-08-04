/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:45:13 by efischer          #+#    #+#             */
/*   Updated: 2019/07/27 13:02:21 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	set_pwd_oldpwd(char *curpath, char *buf, t_list **lst,
			uint8_t flags)
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

static void	init_pwd(t_list **lst)
{
	char	buf[PATH_MAX];
	char	*env_var[3];

	if (ft_getenv("PWD", *lst) == NULL)
	{
		getcwd(buf, PATH_MAX);
		put_name_val_in_tab("PWD", buf, env_var);
		setenv_blt(env_var, lst);
	}
}

static int	check_av(char ***av, uint8_t *flags)
{
	if (flags_cd_blt(av, flags) == FAILURE)
		return (FAILURE);
	if (ft_tablen(*av) > 1)
	{
		ft_putendl_fd("minishell: cd: Too many arguments", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	print_path(char *operand, char *curpath)
{
	if (ft_strequ(operand, "-") == TRUE)
	{
		if (ft_putendl(curpath) == FAILURE)
			ft_putendl_fd("minishell: cd: write error: Bad file descriptor", 2);
	}
}

int			cd_blt(char **av, t_list **lst)
{
	char	*curpath;
	char	*pwd;
	uint8_t	flags;

	av++;
	init_pwd(lst);
	pwd = ft_getenv("PWD", *lst);
	if (check_av(&av, &flags) == FAILURE)
		return (FAILURE);
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
	print_path(*av, curpath);
	ft_strdel(&curpath);
	return (SUCCESS);
}
