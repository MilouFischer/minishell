#include "minishell.h"

static void	set_shlvl(t_list **lst)
{
	char	*shlvl;
	char	*env_var[3];
	int		lvl_val;

	shlvl = ft_getenv("SHLVL", *lst);
	if (shlvl == NULL)
	{
		put_name_val_in_tab("SHLVL", "1", env_var);
		setenv_blt(env_var, lst);
	}
	else
	{
		lvl_val = ft_atoi(shlvl);
		if (lvl_val + 1 > 0)
			shlvl = ft_itoa(lvl_val + 1);
		else
			shlvl = ft_strdup("0");
		put_name_val_in_tab("SHLVL", shlvl, env_var);
		setenv_blt(env_var, lst);
		ft_strdel(&shlvl);
	}
}

void		set_ret(int ret, t_list **lst)
{
	char	*tab[4];
	char	*str_ret;

	str_ret = ft_itoa(ret);
	tab[0] = "RET";
	tab[1] = str_ret;
	tab[2] = "1";
	tab[3] = NULL;
	setenv_blt(tab, lst);
	ft_strdel(&str_ret);
}

void		init_env(t_list **lst)
{
	char	buf[PATH_MAX];
	char	*env_var[3];

	if (ft_getenv("PWD", *lst) == NULL)
	{
		getcwd(buf, PATH_MAX);
		put_name_val_in_tab("PWD", buf, env_var);
		setenv_blt(env_var, lst);
	}
	set_shlvl(lst);
	if (ft_getenv("RET", *lst) == NULL)
		set_ret(0, lst);
}
