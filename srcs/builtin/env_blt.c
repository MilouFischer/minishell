/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_blt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:51:00 by efischer          #+#    #+#             */
/*   Updated: 2019/08/07 13:00:10 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	get_new_env(char *str, t_list **lst)
{
	char	*value;
	char	*name;
	char	*env_var[3];

	value = ft_strchr(str, '=');
	name = ft_strsub(str, 0, value - str);
	value += 1;
	put_name_val_in_tab(name, value, env_var);
	setenv_blt(env_var, lst);
	ft_strdel(&name);
}

static void	change_env(char ***av, t_list **lst)
{
	while (**av != NULL && ft_strchr(**av, '=') != NULL)
	{
		if ((**av)[0] == '=')
			return ;
		get_new_env(**av, lst);
		(*av)++;
	}
}

static void	get_lst_cpy(t_list **local_lst, t_list *lst)
{
	t_list	*new;

	new = NULL;
	while (lst != NULL)
	{
		new = ft_lstcpy(lst, cpy_lst);
		ft_lstaddend(local_lst, new);
		lst = lst->next;
	}
}

int			env_blt(char **av, t_list **lst)
{
	t_list	*local_lst;
	uint8_t	flags;

	av++;
	local_lst = NULL;
	if (flags_env_blt(&av, &flags) == FAILURE)
		return (FAILURE);
	if ((flags & FLAG_I) == FLAG_I)
		local_lst = NULL;
	else
		get_lst_cpy(&local_lst, *lst);
	change_env(&av, &local_lst);
	if (*av != NULL)
	{
		get_new_env("ENV_BLT=1", &local_lst);
		exec_command(av, &local_lst);
	}
	else
		print_env(local_lst, "env");
	ft_lstfree(local_lst, free_env);
	return (SUCCESS);
}
