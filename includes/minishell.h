#ifndef MINISHELL_H
# define MINISHELL_H

# include	<sys/types.h>
# include	<sys/wait.h>
# include	<stdint.h>
# include	"libft.h"

# define ECHO_N		0x01
# define BUF_SIZE	256

void	ft_exit(int status);
int		ft_echo(char **av);
int		cd_blt(char **av);

#endif
