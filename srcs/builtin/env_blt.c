/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_blt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:51:00 by efischer          #+#    #+#             */
/*   Updated: 2019/07/09 15:04:22 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag_i(char ***av)
{
	char	*error;
	size_t	i;

	if (*av == NULL || **av == NULL || (**av)[0] != '-')
		return (FALSE);
	while (**av != NULL && (**av)[0] == '-')
	{
		i = 1;
		while ((**av)[i] != '\0')
		{
			if ((**av)[i] != 'i')
			{
				error = ft_asprintf("env: invalid option -- '%c'", (**av)[i]);
				ft_putstr_fd(error, 2);
				ft_strdel(&error);
				return (FALSE);
			}
			i++;
		}
		ft_strdel(*av);
		(*av)++;
	}
	return (TRUE);
}

static void	get_new_env(char *str, t_list **lst)
{
	char	*value;
	char	*name;

	value = ft_strchr(str, '=');
	name = ft_strsub(str, 0, value - str);
	value += 1;
	setenv_blt(name, value, lst, 1);
	ft_strdel(&name);
}

static void	change_env(char ***av, t_list **lst)
{
	while (**av != NULL && ft_strchr(**av, '=') != NULL)
	{
		if ((**av)[0] == '=')
			return ;
		get_new_env(**av, lst);
		ft_strdel(*av);
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

void		env_blt(char **av, t_list **lst)
{
	char	*tab[2];
	t_list	*local_lst;
	t_list	*head;

	local_lst = NULL;
	if (check_flag_i(&av) == TRUE)
		local_lst = NULL;
	else
		get_lst_cpy(&local_lst, *lst);
	head = local_lst;
	change_env(&av, &local_lst);
	if (*av != NULL)
		exec_command(av, &local_lst);
	else
	{
		tab[0] = "printenv";
		tab[1] = NULL;
		exec_command(tab, &local_lst);
	}
	ft_lstfree(head, free_env);
}
