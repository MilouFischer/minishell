#include "minishell.h"

static void	ft_check_expansion(char **av)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (av[i] != NULL)
	{
		if (ft_strequ(av[i], "~") == TRUE)
		{
			ft_strdel(&av[i]);
			av[i] = ft_strdup(getenv("HOME"));
		}
		else if (av[i][0] == '$')
		{
			tmp = av[i];
			av[i] = ft_strdup(getenv(tmp + 1));
			ft_strdel(&tmp);
		}
		i++;
	}
}

static int	ft_get_command(char ***av)
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

static int	ft_exec_bin(char **av)
{
	char	*path;
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == FAILURE)
		return (FAILURE);
	if (pid > 0)
		wait(&status);
	if (pid == 0)
	{
		path = ft_strjoin("/bin/", av[0]);
		if (execve(path, av, NULL) == FAILURE)
		{
			ft_strdel(&path);
			return (FAILURE);
		}
		ft_strdel(&path);
	}
	return (SUCCESS);
}

static int	ft_exec_builtin(char **av)
{
	char	*path;

	path = ft_strjoin("/home/etienne/Bureau/minishell/builtins/", av[0]);
	if (execve(path, av, NULL) == FAILURE)
	{
		ft_strdel(&path);
		return (FAILURE);
	}
	ft_strdel(&path);
	return (SUCCESS);
}

static int	ft_is_builtin(char *builtin)
{
	if (ft_strequ(builtin, "exit") == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

static int	ft_exec_command(char **av)
{
	if (ft_is_builtin(av[0]) == TRUE)
	{
		if (ft_exec_builtin(av) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (ft_exec_bin(av) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int			main(void)
{
	char	**av;

	av = NULL;
	while (1)
	{
		ft_putstr("$> ");
		if (ft_get_command(&av) == FALSE)
			return (EXIT_FAILURE);
		if (ft_exec_command(av) == FAILURE)
		{
			ft_printf("minishell: command not found: %s\n", av[0]);
			exit(EXIT_FAILURE);
		}
		ft_free_tab(av);
	}
	return (EXIT_SUCCESS);
}
