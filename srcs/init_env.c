/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:59:03 by efischer          #+#    #+#             */
/*   Updated: 2019/08/07 11:31:43 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increase_shlvl(char *shlvl, t_list **lst)
{
	int		lvl_val;
	char	*env_var[3];

	lvl_val = ft_atoi(shlvl);
	if (lvl_val + 1 < 0)
		shlvl = ft_strdup("0");
	else if (lvl_val + 1 >= 1000)
	{
		ft_dprintf(2, "minishell: warning: shell level (%ld) too high, resetting to 1\n", lvl_val + 1);
		shlvl = ft_strdup("1");
	}
	else
		shlvl = ft_itoa(lvl_val + 1);
	put_name_val_in_tab("SHLVL", shlvl, env_var);
	setenv_blt(env_var, lst);
	ft_strdel(&shlvl);
}

static void	set_shlvl(t_list **lst)
{
	char	*shlvl;
	char	*env_var[3];

	shlvl = ft_getenv("SHLVL", *lst);
	if (shlvl == NULL)
	{
		put_name_val_in_tab("SHLVL", "1", env_var);
		setenv_blt(env_var, lst);
	}
	else
		increase_shlvl(shlvl, lst);
}

void		init_env(t_list **lst)
{
	char	buf[PATH_MAX];
	char	*env_var[3];

	if (ft_getenv("PWD", *lst) == NULL)
	{
		getcwd(buf, PATH_MAX);
		put_name_val_in_tab("PWD", buf, env_var);
		setenv_blt(env_var, lst);
	}
	set_shlvl(lst);
}
