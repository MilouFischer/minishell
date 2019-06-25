#include "minishell.h"

void		exit_blt(int status, t_list *env)
{
	ft_lstfree(env, free_env);
	exit(status);
}
