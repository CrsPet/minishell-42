#include "minishell.h"

void	set_fd(t_cmd *cmd_list, int i)
{
	if (!cmd_list->redir_in && cmd_list->pipe_in == pipe_in)
	{
		dup2(shell.fds[i - 1][0], STDIN_FILENO);
	}
	if (cmd_list->pipe_out == pipe_out)
	{
		if (!cmd_list->redir_out)
		{
			if (!cmd_list->next)
				dup2(shell.stdout, STDOUT_FILENO);
			else
				dup2(shell.fds[i][1], STDOUT_FILENO);
		}
	}
}

void	close_fds(int	**fds)
{
	int	i;

	i = 0;
	if (fds)
	{
		while (fds[i])
		{
			close(fds[i][0]);
			close(fds[i][1]);
			i++;
		}
		i = 0;
		while (fds[i])
			free(fds[i++]);
		free(fds);
	}
}

void	wait_pids(pid_t	*pids, int nmb)
{
	int	i;
	int	status;

	i = 0;
	if (pids)
	{
		while (i <= nmb)
		{
			waitpid(pids[i], &status, 0);
			i++;
		}
		shell.status = WEXITSTATUS(status);
		free(pids);
	}
}

void	cmd_end_works(int **fds, pid_t *pids, int i)
{
	close_fds(fds);
	wait_pids(pids, i);
	dup2(shell.stdin, STDIN_FILENO);
	dup2(shell.stdout, STDOUT_FILENO);
}

int	exe(t_cmd *cmd_list, int i)
{
	pid_t	child;
	int		status;

	shell.pids[i] = fork();
	if (-1 == child)
		exit_with_error("Fork error");
	else if (0 == shell.pids[i])
	{
		set_fd(cmd_list, i);
		close_fds(shell.fds);
		execve(cmd_list->args[0], cmd_list->args, shell.env);
		perror("ERROR");
		exit (1);
	}
	return (1);
}

int	try_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		change_dir();
	else if (!ft_strcmp(args[0], "env"))
		env();
	else if (!ft_strcmp(args[0], "pwd"))
		pwd();
	else if (!ft_strcmp(args[0], "export"))
		export();
	else if (!ft_strcmp(args[0], "unset"))
		unset(args, shell.env);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args);
	else
		return (0);
	return (1);
}

void	open_redirs(t_cmd *cmd_list)
{
	if (cmd_list->redir_in)
	{
		set_redir_in(cmd_list->redir_in);
	}
	if (cmd_list->redir_out)
	{
		set_redir_out(cmd_list->redir_out);
	}
}

int	exec(void)
{
	int	i;

	i = 0;
	get_pids_fds(shell.cmd_list);
	while (shell.cmd_list)
	{
		open_redirs(shell.cmd_list);
		if (shell.cmd_list->args[0] && !try_builtin (shell.cmd_list->args))
		{
			if (parse_cmds(shell.cmd_list))
			{
				exe(shell.cmd_list, i);
				i++;
			}
		}
		shell.cmd_list = shell.cmd_list->next;
	}
	cmd_end_works(shell.fds, shell.pids, i);
	return (0);
}
