/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:27:40 by efischer          #+#    #+#             */
/*   Updated: 2019/08/07 16:39:06 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_follow(char *str)
{
	char	**tab;
	size_t	i;

	i = 0;
	if (ft_strchr(str, ';') == NULL)
		return (TRUE);
	else if (str != NULL && (str[0] == ';' || ft_strstr(str, ";;") != NULL))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return (FALSE);
	}
	tab = ft_strsplit(str, ';');
	while (tab[i] != NULL)
	{
		if (ft_str_is_blank(tab[i]) == TRUE)
		{
			ft_free_tab(tab);
			ft_putendl_fd("minishell: syntax error", 2);
			return (FALSE);
		}
		i++;
	}
	ft_free_tab(tab);
	return (TRUE);
}

void	keep_tab(char **tab_operand, uint8_t opt)
{
	static char **tab_cp;

	if (opt == INIT_TAB)
		tab_cp = tab_operand;
	else
		ft_free_tab(tab_cp);
}

int		print_env(t_list *lst, char *utility)
{
	if (ft_lstprint(lst, get_content_to_print) == FAILURE)
	{
		ft_dprintf(2, "minishell: %s: write error: Bad file descriptor\n",
		utility);
		return (FAILURE);
	}
	return (SUCCESS);
}

int		print_env_one(t_list *lst, char *utility, char *env_var)
{
	t_list	*tmp;

	tmp = find_env(env_var, lst);
	if (tmp != NULL && ft_strequ(((t_env*)(tmp->content))->name, "RET")
		== FALSE)
	{
		if (ft_putendl(((t_env*)(tmp->content))->value) == FAILURE)
		{
			ft_dprintf(2, "minishell: %s: write error: Bad file descriptor\n",
			utility);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
