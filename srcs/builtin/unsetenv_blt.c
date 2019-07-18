#include "minishell.h"

int		unsetenv_blt(char **av, t_list **lst)
{
	t_list	*head;
	t_list	*del_env;

	av++;
	head = *lst;
	if (*av == NULL)
		return (FAILURE);
	del_env = find_env(*av, *lst);
	if (del_env == NULL)
		return (SUCCESS);
	while ((*lst)->next != NULL && (*lst)->next != del_env)
		*lst = (*lst)->next;
	(*lst)->next = del_env->next;
	*lst = head;
	ft_lstdelone(&del_env, free_env);
	return (SUCCESS);
}
