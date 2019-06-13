#include "minishell.h"

static int	ft_get_command(char **buf)
{
	if (get_next_line(0, buf) == FALSE)
	{
		ft_strdel(buf);
		ft_putstr("minishell: error read input");
		return (FALSE);
	}
	return (TRUE);
}

int			main(void)
{
	char	*buf;

	buf = NULL;
	while (1)
	{
		ft_putstr("$> ");
		if (ft_get_command(&buf) == FALSE)
			return (EXIT_FAILURE);
		ft_putstr(buf);
//		if (ft_exec_command(buf) == FAILURE)
//			ft_printf("minishell: command not found: %s", buf);
		ft_strdel(&buf);
		ft_putchar('\n');
	}
	return (EXIT_SUCCESS);
}
