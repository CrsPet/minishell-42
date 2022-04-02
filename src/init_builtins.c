#include "minishell.h"

void	set_builtin_names(t_minishell *shell)
{
	char	*all_builtins;

	all_builtins = ft_strdup("change_dir env echo exit export pwd unset");
	if (NULL == all_builtins)
		exit_with_error("minishell: -: malloc error");
	shell->builtin_names = ft_split(all_builtins, ' ');
	free(all_builtins);
	if (NULL == shell->builtin_names)
		exit_with_error("minishell: -: malloc error");
}

void	set_builtin_funcs(t_minishell *shell)
{
	shell->builtin_funcs[0] = change_dir;
	shell->builtin_funcs[1] = env;
	shell->builtin_funcs[2] = echo;
	shell->builtin_funcs[3] = ft_exit;
	shell->builtin_funcs[4] = export;
	shell->builtin_funcs[5] = pwd;
	shell->builtin_funcs[6] = unset;
}