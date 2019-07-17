#include "minishell.h"

void		exit_blt(char **av, t_list **lst)
{
	int		status;

	status = 0;
	if (av[1] != NULL)
		status = ft_atoi(av[1]);
	ft_free_tab(av);
	ft_lstfree(*lst, free_env);
	exit(status);
}
