/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:42:07 by efischer          #+#    #+#             */
/*   Updated: 2019/08/07 19:15:40 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bracket(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '{' && str[i] != '}')
		i++;
	if (str[i] == '\0' || str[i] == '}')
		return (SUCCESS);
	if (str[i + 1] == '}')
		return (FAILURE);
	i++;
	while (str[i] != '\0' && str[i] != '}')
	{
		if (str[i] == '{')
			return (FAILURE);
		i++;
	}
	if (str[i] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

static int	check_bracket(char *str)
{
	char	**tab;
	size_t	i;

	i = 0;
	tab = ft_strsplit(str, '$');
	if (tab == NULL)
		return (FAILURE);
	while (tab[i] != NULL)
	{
		if (bracket(tab[i]) == FAILURE)
		{
			ft_free_tab(tab);
			return (FAILURE);
		}
		i++;
	}
	ft_free_tab(tab);
	return (SUCCESS);
}

static char	*special_operand(char *av, size_t *i)
{
	char	*new_av;

	new_av = NULL;
	if (av[*i] == '\0')
		new_av = ft_strdup("$");
	else if (av[*i] == '$')
	{
		new_av = ft_itoa(getpid());
		(*i)++;
	}
	else if (av[*i] == '?')
	{
		new_av = ft_itoa(g_ret);
		(*i)++;
	}
	return (new_av);
}

static char	*get_operand(char *av, size_t *i, uint8_t flag)
{
	char	*operand;
	size_t	count;

	count = *i;
	while (av[count] != '\0' && av[count] != '$' && av[count] != '/'
		&& av[count] != ':')
	{
		if (av[count] == '}' && flag == 1)
			break ;
		count++;
	}
	operand = ft_strndup(av + *i, count - *i);
	*i = count;
	return (operand);
}

static char	*process_operand(char *av, size_t *i, t_list *lst)
{
	char	*new_av;
	char	*operand;
	uint8_t	flag;

	flag = 0;
	if (av[*i] == '\0' || av[*i] == '$' || av[*i] == '?')
		return (special_operand(av, i));
	if (av[*i] == '{')
	{
		flag = 1;
		(*i)++;
	}
	operand = get_operand(av, i, flag);
	new_av = ft_strdup(ft_getenv(operand, lst));
	ft_strdel(&operand);
	if (av[*i] == '}' && flag == 1)
		(*i)++;
	return (new_av);
}

int			process_dollar(char **av, t_list *lst)
{
	size_t	i;
	char	*new_av;
	char	*pre_operand;
	char	*expanded;
	char	*tmp;

	i = 0;
	new_av = NULL;
	if (check_bracket(*av) == FAILURE)
	{
		ft_dprintf(2, "minishell: %s: Bad substitution\n", *av);
		return (FAILURE);
	}
	while ((tmp = ft_strchr(*av + i, '$')) != NULL)
	{
		pre_operand = ft_strsub(*av, i, tmp - (*av + i));
		i += ft_strlen(pre_operand) + 1;
		expanded = process_operand(*av, &i, lst);
		expanded = ft_join_free(pre_operand, expanded, 3);
		new_av = ft_join_free(new_av, expanded, 3);
	}
	new_av = ft_join_free(new_av, *av + i, 1);
	ft_strdel(av);
	*av = new_av;
	return (SUCCESS);
}
