/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_blt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:51:00 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 16:15:11 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int		ft_check_arg(char *arg, uint8_t *flags)
{
	size_t	i;

	i = 1;
	while (arg[i] != '\0')
	{
		*flags = 0;
		if (arg[i] == 'i')
			*flags |= FLAG_I;
		else
		{
			ft_putstr_fd("minishell: env: -", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putendl_fd(": Invalid option", 2);
			ft_putstr_fd("usage: env [-i] [name=value]...", 2);
			ft_putendl_fd("[utility [argument...]]", 2);
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
		if (ft_strequ(**av, "--") == TRUE)
		{
			(*av)++;
			return (SUCCESS);
		}
		else if (ft_check_arg(**av, flags) == FALSE)
			return (FAILURE);
		(*av)++;
	}
	return (SUCCESS);
}

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

int			env_blt(char **av, t_list **lst)
{
	char	*tab[2];
	t_list	*local_lst;
	t_list	*head;
	uint8_t	flags;

	av++;
	local_lst = NULL;
	if (get_flags(&av, &flags) == FAILURE)
		return (FAILURE);
	if ((flags & FLAG_I) == FLAG_I)
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
	return (SUCCESS);
}
