#ifndef MINISHELL_H
# define MINISHELL_H

# include	<sys/types.h>
# include	<sys/wait.h>
# include	<stdint.h>
# include	"libft.h"

# define ECHO_N	0x01
# define ECHO_E 0x02

void	ft_exit(int status);
int		ft_echo(char **av);

#endif
