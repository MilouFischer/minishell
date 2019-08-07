/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:19:31 by efischer          #+#    #+#             */
/*   Updated: 2019/08/07 13:44:02 by efischer         ###   ########.fr       */
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

void		process_tilde(char **av, t_list *lst)
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

static char	*special_dolar_operand(char c)
{
	char	*new_av;

	new_av = NULL;
	if (c == '\0')
		new_av = ft_strdup("$");
	else if (c == '?')
		new_av = ft_itoa(g_ret);
	return (new_av);
}

static char	*check_dollar_operand(char *av, size_t *i, t_list *lst)
{
	char	*new_av;
	char	*operand;
	char	*tmp;

	(*i)++;
	new_av = NULL;
	if (av[*i] == '\0' || av[*i] == '?' || av[*i] == '$')
	{
		new_av = special_dolar_operand(av[*i]);
		(*i)++;
		return (new_av);
	}
	tmp = av + *i;
	if (av[*i] == '{' && ft_strchr(av, '}') != NULL)
	{
		while (av[*i] != '\0' && av[*i] != '}')
			(*i)++;
		operand = ft_strsub(tmp, 1, *i - 2);
		(*i)++;
	}
	else
	{
		while (av[*i] != '\0' && av[*i] != '$' && av[*i] != '/' && av[*i] != ':')
			(*i)++;
		operand = ft_strndup(tmp, *i - 1);
	}
	new_av = ft_strdup(ft_getenv(operand, lst));
	ft_strdel(&operand);
	return (new_av);
}

void		process_dollar(char **av, t_list *lst)
{
	size_t	i;
	size_t	tmp_i;
	char	*new_av;
	char	*tmp;

	i = 0;
	new_av = NULL;
	while ((*av)[i] != '\0')
	{
		tmp_i = i;
		while ((*av)[tmp_i] != '\0' && (*av)[tmp_i] != '$')
			tmp_i++;
		tmp = ft_strndup((*av) + i, tmp_i - i);
		i = tmp_i;
		new_av = ft_join_free(new_av, tmp, 3);
		if ((*av)[i] != '\0')
		{
			tmp = check_dollar_operand(*av, &i, lst);
			new_av = ft_join_free(new_av, tmp, 3);
		}
	}
	ft_strdel(av);
	*av = new_av;
}
