#ifndef MINISHELL_H
# define MINISHELL_H

# include	<sys/types.h>
# include	<sys/wait.h>
# include	<stdint.h>
# include	"libft.h"

# define ECHO_N		0x01

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

void	exit_blt(int status, t_list *env);
int		echo_blt(char **av);
int		cd_blt(char **av, t_list **lst);
t_list	*find_env(const char *arg, t_list *lst);
void	get_env_lst(char **envp, t_list **lst);
void	printenv_blt(char **av, t_list *lst);
void	get_content_to_print(t_list *lst, t_list **elem);
char	*get_content_to_tab(t_list *lst);
void	free_env(void *content, size_t content_size);
int		setenv_blt(const char *name, const char *val, t_list **lst,
			int overwrite);
void	pwd_blt(t_list *lst);
int		ft_get_command(char ***av);
char	*ft_getenv(char *env_name, t_list *lst);
int		unsetenv_blt(const char *name, t_list **lst);
void	env_blt(char **av, t_list *lst);
int		exec_command(char **av, t_list **lst);

#endif
