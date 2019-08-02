/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_blt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 11:38:36 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 12:38:32 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_list	*check_name(const char *name, t_list *lst, char *overwrite)
{
	if (ft_strequ(name, "RET") == TRUE && ft_strequ(overwrite, "1") == FALSE)
		return (NULL);
	while (lst != NULL)
	{
		if (ft_strequ(name, ((t_env*)(lst->content))->name) == TRUE)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static void		add_env(const char *name, const char *val, t_list **lst)
{
	t_env	env;

	ft_bzero(&env, sizeof(env));
	env.name = ft_strdup(name);
	env.value = ft_strdup(val);
	ft_lstaddend(lst, ft_lstnew(&env, sizeof(env)));
}

static int		name_is_alnum(char *name)
{
	size_t	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (ft_isalnum(name[i]) == FALSE && name[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void		new_env_var(char *name, char *val, char *overwrite,
				t_list **lst)
{
	t_list	*head;

	head = *lst;
	*lst = check_name(name, *lst, overwrite);
	if (*lst != NULL)
	{
		ft_strdel(&((t_env*)((*lst)->content))->value);
		((t_env*)((*lst)->content))->value = ft_strdup(val);
	}
	else
		add_env(name, val, &head);
	*lst = head;
}

int				setenv_blt(char **av, t_list **lst)
{
	char	*name;
	char	*val;
	char	*overwrite;

	if (ft_strequ(av[0], "setenv") == TRUE)
		av++;
	if (*av == NULL)
		return (SUCCESS);
	name = av[0];
	val = av[1];
	overwrite = NULL;
	if (val == NULL)
		val = "\0";
	else
		overwrite = av[2];
	if (name_is_alnum(name) == FALSE)
	{
		ft_putendl_fd("minishell: setenv: invalid syntax", 2);
		return (FAILURE);
	}
	new_env_var(name, val, overwrite, lst);
	return (SUCCESS);
}
