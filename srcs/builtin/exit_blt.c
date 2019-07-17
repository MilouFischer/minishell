#include "minishell.h"

void		exit_blt(char **av, t_list **lst)
{
	int		status;

	status = 0;
	if (*av != NULL)
		status = ft_atoi(*av);
	ft_free_tab(av);
	ft_lstfree(*lst, free_env);
	exit(status);
}
