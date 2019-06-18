#include "minishell.h"

void		ft_exit(int status, t_list *env)
{
	ft_lstfree(env, free_env);
	exit(status);
}
