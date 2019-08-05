/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:19:31 by efischer          #+#    #+#             */
/*   Updated: 2019/08/05 13:56:30 by efischer         ###   ########.fr       */
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

static char	*check_dollar_operand(char **av, size_t *i, t_list *lst)
{
	char	*operand;
	char	*env;
	char	*new_av;
	size_t	op_i;

	(*i)++;
	op_i = *i;
	new_av = NULL;
	operand = NULL;
	if ((*av)[*i] == '?')
		new_av = ft_itoa(ret_value);
	if ((*av)[*i] != '\0')
	{
		while ((*av)[op_i] != '\0' && ft_isalnum((*av)[op_i]) == TRUE)
		{
			op_i++;
			operand = ft_strndup((*av) + *i, op_i - *i);
			if ((env = ft_getenv(operand, lst)) != NULL)
			{
				*i = op_i;
				ft_strdel(&operand);
				new_av = ft_strdup(env);
				if ((*av)[*i] != '$')
					new_av = ft_join_free(new_av, (*av) + *i, 1);
				return (new_av);
			}
			ft_strdel(&operand);
		}
	}
	else if ((*av)[*i] == '\0') 
		new_av = ft_strdup("$");
	(*i)++;
	return (new_av);
}

void		process_dollar(char **av, t_list *lst)
{
	size_t	i;
	char	*tmp;
	char	*new_av;

	i = 0;
	new_av = NULL;
	while ((*av)[i] != '\0' && (*av)[i] != '$')
		i++;
	tmp = ft_strsub(*av, 0, i);
	while ((*av)[i] == '$')
		new_av = ft_join_free(new_av, check_dollar_operand(av, &i, lst), 3);
	if ((*av)[i] == '/')
		new_av = ft_join_free(new_av, (*av) + i, 1);
	new_av = ft_join_free(tmp, new_av, 3);
	ft_strdel(av);
	*av = new_av;
}
