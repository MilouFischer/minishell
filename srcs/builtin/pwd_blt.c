#include "minishell.h"

void	pwd_blt(t_list *lst)
{
	char	*pwd[2];

	pwd[0] = "PWD";
	pwd[1] = NULL;
	printenv_blt(pwd, lst);
}
