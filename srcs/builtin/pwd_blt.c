#include "minishell.h"

void	pwd_blt(char **av, t_list **lst)
{
	char	*pwd[3];

	(void)av;
	pwd[0] = NULL;
	pwd[1] = "PWD";
	pwd[2] = NULL;
	printenv_blt(pwd, lst);
}
