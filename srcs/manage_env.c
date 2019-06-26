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
		tab = ft_strsplit(envp[i], '=');
		env.name = ft_strdup(*tab++);
		while (*tab != NULL)
		{
			env.value = ft_join_free(env.value, *tab, 1);
			tab++;
			if (*tab != NULL)
				env.value = ft_join_free(env.value, "=", 1);
		}
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
