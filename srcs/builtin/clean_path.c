/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 12:31:00 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 12:35:25 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	fill_index_tab(int **index_tab, char **tab, ssize_t i)
{
	size_t	dot_count;

	dot_count = 0;
	while (i > 0)
	{
		i--;
		if (ft_strequ(tab[i], ".") == TRUE)
			(*index_tab)[i] = 0;
		else if (ft_strequ(tab[i], "..") == TRUE)
		{
			(*index_tab)[i] = 0;
			dot_count++;
		}
		else if (dot_count > 0)
		{
			(*index_tab)[i] = 0;
			dot_count--;
		}
		else
			(*index_tab)[i] = 1;
	}
}

static int	*get_index_tab(char **tab)
{
	int		*index_tab;
	ssize_t	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	index_tab = (int*)malloc(sizeof(int) * i);
	ft_bzero(index_tab, i);
	fill_index_tab(&index_tab, tab, i);
	return (index_tab);
}

static char	*path_cleaning(char *path)
{
	char	**tab;
	char	*clean_path;
	int		*index_tab;
	size_t	i;

	i = 0;
	clean_path = NULL;
	tab = ft_strsplit(path, '/');
	if (tab == NULL)
		return (NULL);
	index_tab = get_index_tab(tab);
	while (tab[i] != NULL)
	{
		if (index_tab[i] > 0)
		{
			clean_path = ft_join_free(clean_path, "/", 1);
			clean_path = ft_join_free(clean_path, tab[i], 1);
		}
		i++;
	}
	if (clean_path == NULL)
		clean_path = ft_join_free(clean_path, "/", 1);
	ft_free_tab(tab);
	free(index_tab);
	return (clean_path);
}

void		get_clean_path(char **path)
{
	char	*clean_path;

	clean_path = NULL;
	if (path == NULL || *path == NULL)
		return ;
	clean_path = path_cleaning(*path);
	ft_strdel(path);
	*path = ft_strdup(clean_path);
	ft_strdel(&clean_path);
}
