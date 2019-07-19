#ifndef MINISHELL_H
# define MINISHELL_H

# include	<sys/types.h>
# include	<sys/wait.h>
# include	<stdint.h>
# include	"libft.h"

# define ECHO_N			0x01
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
# define F_BLT			CD_BLT, EXIT_BLT, PWD_BLT, ECHO_BLT, ENV_BLT, SETENV_BLT, UNSETENV_BLT, PRINTENV_BLT

//typedef int		(t_builtin *)(char **av, t_list **env);
typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

int		exit_blt(char **av, t_list **lst);
int		echo_blt(char **av, t_list **lst);
int		cd_blt(char **av, t_list **lst);
int		printenv_blt(char **av, t_list **lst);
int		setenv_blt(char **av, t_list **lst);
int		pwd_blt(char **av, t_list **lst);
int		env_blt(char **av, t_list **lst);
int		unsetenv_blt(char **av, t_list **lst);

t_list	*find_env(const char *arg, t_list *lst);
void	get_env_lst(char **envp, t_list **lst);
void	get_content_to_print(t_list *lst, t_list **elem);
char	*get_content_to_tab(t_list *lst);
void	free_env(void *content, size_t content_size);
int		ft_get_command(char ***av, t_list *lst);
char	*ft_getenv(char *env_name, t_list *lst);
int		exec_command(char **av, t_list **lst);
t_list	*cpy_lst(t_list	*lst);
void	init_env(t_list **lst);
void	put_name_val_in_tab(char *name, char *value, char **env_var);

#endif
