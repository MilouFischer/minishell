#include "minishell.h"

int		cd_blt(char **av, t_list **lst)
{
	char	*curpath;
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	if (*av == NULL && ft_getenv("HOME", lst) == NULL)
		return (SUCCESS);
	else if (*av == NULL && ft_getenv("HOME", lst) != NULL)
		curpath = ft_strdup(ft_getenv("HOME", lst));
	else if (*av != NULL && *av[0] == '/')
		curpath = ft_strdup(*av);
	else if (*av != NULL && *av[0] == '.' && (*av[1] == '\0' || (*av[1] == '.' && *av[2] == '\0')))
		curpath == ft_strdup(*av);
	
}
