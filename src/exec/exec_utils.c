#include "minishell.h"

static int	is_builtin(char *arg)
{
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "env")
		|| !ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}

static int	get_exec_nmb(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->args[0] && !is_builtin(cmd->args[0]))
			i++;
		cmd = cmd->next;
	}
	return (i);
}

void	get_pids_fds(t_cmd *cmd_list)
{
	int	exec_nmb;
	int	i;

	i = 0;
	shell.pids = NULL;
	shell.fds = NULL;
	exec_nmb = get_exec_nmb(cmd_list);
	if (exec_nmb)
	{
		shell.pids = (pid_t *)malloc(sizeof(pid_t) * exec_nmb );
		if (NULL == shell.pids)
			exit_with_error("Malloc error");
		shell.fds = (int **)malloc(sizeof(int *) * exec_nmb);
		if (NULL == shell.pids)
			exit_with_error("Malloc error");
		while (i < exec_nmb - 1)
		{
			shell.fds[i] = (int *)malloc(sizeof(int) * 2);
			if (-1 == pipe(shell.fds[i]))
				exit_with_error("Pipe error");
			i++;
		}
		shell.fds[exec_nmb - 1] = NULL;
	}
}
