#ifndef MINISHELL_H
# define MINISHELL_H

# include	<sys/types.h>
# include	<sys/wait.h>
# include	<stdint.h>
# include	"libft.h"

# define ECHO_N		0x01
# define BUF_SIZE	256

typedef struct	s_env
{
	char		*name;
	char		*value;
	char		*all;
}				t_env;

void	ft_exit(int status, t_list *env);
int		ft_echo(char **av);
int		cd_blt(char **av, t_list *lst);
t_list	*find_env(char *arg, t_list *lst);
void	get_env_lst(char **envp, t_list **lst);
void	printenv_blt(char **av, t_list *lst);

#endif
