#include "minishell.h"

static void	free_env(void *content)
{
	ft_strdel(&((t_env*)content)->name);
	ft_strdel(&((t_env*)content)->value);
	ft_strdel(&((t_env*)content)->all);
	free(content);
}

void		ft_exit(int status, t_list *env)
{
	ft_lstfree(env, free_env);
	exit(status);
}
