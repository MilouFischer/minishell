/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 09:50:50 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 12:35:53 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

# define CD				"cd"
# define EXIT			"exit"
# define PWD			"pwd"
# define ECHO			"echo"
# define ENV			"env"
# define SETENV			"setenv"
# define UNSETENV		"unsetenv"
# define PRINTENV		"printenv"
# define BUILTIN		CD, EXIT, PWD, ECHO, ENV, SETENV, UNSETENV, PRINTENV
# define NB_OF_BLT		8
# define CD_BLT			cd_blt
# define EXIT_BLT		exit_blt
# define PWD_BLT		pwd_blt
# define ECHO_BLT		echo_blt
# define ENV_BLT		env_blt
# define SETENV_BLT		setenv_blt
# define UNSETENV_BLT	unsetenv_blt
# define PRINTENV_BLT	printenv_blt

int		exit_blt(char **av, t_list **lst);
int		echo_blt(char **av, t_list **lst);
int		cd_blt(char **av, t_list **lst);
int		printenv_blt(char **av, t_list **lst);
int		setenv_blt(char **av, t_list **lst);
int		pwd_blt(char **av, t_list **lst);
int		env_blt(char **av, t_list **lst);
int		unsetenv_blt(char **av, t_list **lst);
char	*get_path(char *dir_op, t_list *lst);
void	get_clean_path(char **path);
int		change_dir(char *curpath, char *dir_op, t_list **lst);

#endif
