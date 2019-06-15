/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 15:25:50 by efischer          #+#    #+#             */
/*   Updated: 2019/06/15 16:08:42 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env_lst(char **envp, t_list **lst)
{
	t_env	env;
	char	**tab;
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_bzero(&env, sizeof(env));
		env.all = ft_strdup(envp[i]);
		tab = ft_strsplit(envp[i], '=');
		env.name = ft_strdup(tab[0]);
		env.value = ft_strdup(tab[1]);
		ft_free_tab(tab);
		ft_lstaddend(lst, ft_lstnew(&env, sizeof(env)));
		i++;
	}
}

t_list	*find_env(char *arg, t_list *lst)
{
	while (lst != NULL)
	{
		if (ft_strequ(((t_env*)(lst->content))->name, arg) == TRUE)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	setenv_blt(char *name, char *value, t_list *lst)
{
	t_list *tmp;

	tmp = find_env(name, lst);
	if (tmp != NULL)
	{
		ft_strdel(&((t_env*)(tmp->content))->value);
		((t_env*)(tmp->content))->value = ft_strdup(value);
	}
}
