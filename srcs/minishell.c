/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:05:15 by efischer          #+#    #+#             */
/*   Updated: 2019/06/15 16:20:02 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	ft_exec_bin(char **av, char **envp)
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
		if (execve(path, av, envp) == FAILURE)
		{
			ft_strdel(&path);
			return (FAILURE);
		}
		ft_strdel(&path);
	}
	return (SUCCESS);
}

static int	ft_exec_builtin(char **av, t_list *lst)
{
	int		status;

	status = 0;
	if (ft_strequ(av[0], "exit") == TRUE)
	{
		if (av[1] != NULL)
			status = ft_atoi(av[1]);
		ft_free_tab(av);
		ft_exit(status);
	}
	else if (ft_strequ(av[0], "echo") == TRUE)
		ft_echo(av + 1);
	else if (ft_strequ(av[0], "cd") == TRUE)
		cd_blt(av + 1, lst);
	else if (ft_strequ(av[0], "printenv") == TRUE)
		printenv_blt(av + 1, lst);
	else
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_exec_command(char **av, char **envp, t_list *lst)
{
	if (*av == NULL)
		return (SUCCESS);
	if (ft_exec_builtin(av, lst) == FAILURE)
	{
		if (ft_exec_bin(av, envp) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int			main(int ac, char **av, char **envp)
{
	char	**tab;
	t_list	*lst;

	(void)ac;
	(void)av;
	lst = NULL;
	ft_bzero(&lst, sizeof(lst));
	get_env_lst(envp, &lst);
	while (1)
	{
		tab = NULL;
		ft_putstr("$> ");
		if (ft_get_command(&tab) == FALSE)
		{
			ft_free_tab(tab);
			return (EXIT_FAILURE);
		}
		if (ft_exec_command(tab, envp, lst) == FAILURE)
		{
			ft_printf("minishell: command not found: %s\n", tab[0]);
			ft_free_tab(tab);
			exit(EXIT_FAILURE);
		}
		ft_free_tab(tab);
	}
	return (EXIT_SUCCESS);
}
