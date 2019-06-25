#include "minishell.h"

static void	ft_process_tilde(char **arg)
{
	if (ft_strequ(*arg, "~") == TRUE)
	{
		ft_strdel(arg);
		*arg = ft_strdup(getenv("HOME"));
	}
	else if (ft_strequ(*arg, "~+") == TRUE)
	{
		ft_strdel(arg);
		*arg = ft_strdup(getenv("PWD"));
	}
	else if (ft_strequ(*arg, "~-") == TRUE)
	{
		ft_strdel(arg);
		*arg = ft_strdup(getenv("OLDPWD"));
	}
}

static void	ft_check_expansion(char **av)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '~')
			ft_process_tilde(&av[i]);
		else if (av[i][0] == '$')
		{
			tmp = av[i];
			av[i] = ft_strdup(getenv(tmp + 1));
			ft_strdel(&tmp);
		}
		i++;
	}
}

int			ft_get_command(char ***av)
{
	char *buf;

	buf = NULL;
	if (get_next_line(0, &buf) == FALSE)
	{
		ft_strdel(&buf);
		ft_putstr("minishell: error read input\n");
		return (FALSE);
	}
	*av = ft_strsplit(buf, ' ');
	ft_strdel(&buf);
	if (*av == NULL)
	{
		ft_putstr("minishell: error read input\n");
		return (FALSE);
	}
	ft_check_expansion(*av);
	return (TRUE);
}
