/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 09:50:52 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 11:30:54 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h>
# include "libft.h"
# include "builtin.h"

# define ECHO_N	0x01

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

t_list			*find_env(const char *arg, t_list *lst);
void			get_env_lst(char **envp, t_list **lst);
void			get_content_to_print(t_list *lst, t_list **elem);
char			*get_content_to_tab(t_list *lst);
void			free_env(void *content, size_t content_size);
int				ft_get_command(char ***av, t_list *lst);
char			*ft_getenv(char *env_name, t_list *lst);
int				exec_command(char **av, t_list **lst);
t_list			*cpy_lst(t_list	*lst);
void			init_env(t_list **lst);
void			put_name_val_in_tab(char *name, char *value, char **env_var);
void			process_dollar(char **av, t_list *lst);
void			process_tilde(char **av, t_list *lst);
int				exec_builtin(char **av, t_list **lst);
int				exec_bin(char **av, t_list **lst);

#endif
