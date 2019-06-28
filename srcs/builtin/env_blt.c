# include "minishell.h"

static int	check_flag_i(char **av)
{
	char	*error;
	size_t	i;

	if (av == NULL || *av == NULL || (*av)[0] != '-')
		return (FALSE);
	while (*av != NULL && (*av)[0] == '-')
	{
		i = 1;
		while ((*av)[i] != '\0')
		{
			if ((*av)[i] != 'i')
			{
				error = ft_asprintf("env: invalid option -- '%c'", (*av)[i]);
				ft_putstr_fd(error, 2);
				ft_strdel(&error);
				return (FALSE);
			}
			i++;
		}
		ft_strdel(av);
		av++;
	}
	return (TRUE);
}

/*static void	change_env(char **av, t_list **lst)
{
	t_env	env;

	while (*av != NULL && ft_strchr(*av, '=') != NULL)
	{
		if ((*av)[0] == '=')
			return ;
		env = get_new_env(*av);
		setenv_blt(env.name, env.value, lst, 1);
		ft_strdel(av);
		av++;
	}
}*/

void		env_blt(char **av, t_list *lst)
{
	char	*tab[2];

	if (check_flag_i(av) == TRUE)
		lst = NULL;
//	change_env(av, &lst);
	if (*av != NULL)
		exec_command(av, &lst);
	else
	{
		tab[0] = "printenv";
		tab[1] = NULL;
		exec_command(tab, &lst);
	}
}
