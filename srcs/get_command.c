/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 11:56:37 by efischer          #+#    #+#             */
/*   Updated: 2019/07/18 14:43:57 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_tilde_operand(char **av, char *tilde_part, char *rest_arg,
			t_list *lst)
{
	if (ft_strequ(tilde_part, "~") == TRUE)
	{
		ft_strdel(av);
		*av = ft_strjoin(ft_getenv("HOME", lst), rest_arg);
	}
	else if (ft_strequ(tilde_part, "~+") == TRUE)
	{
		ft_strdel(av);
		*av = ft_strjoin(ft_getenv("PWD", lst), rest_arg);
	}
	else if (ft_strequ(tilde_part, "~-") == TRUE)
	{
		ft_strdel(av);
		*av = ft_strjoin(ft_getenv("OLDPWD", lst), rest_arg);
	}
}

static void	process_tilde(char **av, t_list *lst)
{
	char	*rest_arg;
	char	*tilde_part;

	rest_arg = ft_strchr(*av, '/');
	if (rest_arg == NULL)
		tilde_part = ft_strdup(*av);
	else
		tilde_part = ft_strsub(*av, 0, rest_arg - *av);
	rest_arg = ft_strdup(rest_arg);
	check_tilde_operand(av, tilde_part, rest_arg, lst);
	ft_strdel(&rest_arg);
	ft_strdel(&tilde_part);
}

static void	check_dollar_operand(char **av, size_t *i, char **new_av, t_list *lst)
{
	char	*operand;
	char	*env;
	size_t	op_i;

	operand = NULL;
	(*i)++;
	op_i = *i;
	if ((*av)[*i] != '\0' && (*av)[*i] != '$')
	{
		while ((*av)[op_i] != '\0' && ft_isalnum((*av)[op_i]) == TRUE)
			op_i++;
		operand = ft_strndup(*av + *i, op_i - *i);
		*i = op_i;
		if ((env = ft_getenv(operand, lst)) != NULL)
		{
			ft_strdel(&operand);
			operand = ft_strdup(env);
		}
		*new_av = ft_join_free(*new_av, operand, 3);
	}
	else
		*new_av = ft_join_free(*new_av, "$", 1);
}

static void	process_dollar(char **av, t_list *lst)
{
	size_t	i;
	char	*new_av;

	i = 0;
	new_av = NULL;
	while ((*av)[i] != '\0')
	{
		if ((*av)[i] == '$')
			check_dollar_operand(av, &i, &new_av, lst);
		else
			i++;
	}
	if (new_av != NULL)
	{
		ft_strdel(av);
		*av = new_av;
	}
}

static void	check_expansion(char **av, t_list *lst)
{
	size_t	i;

	i = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '~')
			process_tilde(&av[i], lst);
		else if (av[i][0] == '$')
			process_dollar(&av[i], lst);
		i++;
	}
}

int			ft_get_command(char ***av, t_list *lst)
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
	check_expansion(*av, lst);
	return (TRUE);
}
