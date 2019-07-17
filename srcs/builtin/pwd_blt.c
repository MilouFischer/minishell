#include "minishell.h"

void	pwd_blt(char **av, t_list **lst)
{
	char	*pwd[2];

	(void)av;
	pwd[0] = "PWD";
	pwd[1] = NULL;
	printenv_blt(pwd, lst);
}
