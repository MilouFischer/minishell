#include "minishell.h"

static t_list	*check_name(const char *name, t_list *lst)
{
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
	t_env	*env;

	ft_bzero(&env, sizeof(env));
	env->name = ft_strdup(name);
	env->value = ft_strdup(val);
	ft_lstaddend(lst, ft_lstnew(&env, sizeof(env)));
}

int				setenv_blt(const char *name, const char *val, t_list **lst,
				int overwrite)
{
	t_list	*head;

	head = *lst;
	if (name == NULL || *lst == NULL)
		return (FAILURE);
	if (ft_strchr(name, '=') != NULL)
		return (FAILURE);
	*lst = check_name(name, *lst);
	if (*lst != NULL)
	{
		if (overwrite > 0)
			((t_env*)((*lst)->content))->value = ft_strdup(val);
	}
	else
		add_env(name, val, &head);
	*lst = head;
	return (SUCCESS);
}
