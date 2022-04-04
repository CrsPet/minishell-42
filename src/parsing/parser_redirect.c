/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 21:18:27 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 18:55:42 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_redir_in_2(char **cmd, int i)
{
	if (!cmd[i + 1])
		return (error_parser(\
		"minishell: syntax error near unexpected token `newline'"));
	ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redir_in, \
	ft_lstnew_redir(ft_strdup(cmd[i + 1]), redir_in_2));
	return (1);
}

int	add_redir_out_2(char **cmd, int i)
{
	if (!cmd[i + 1])
		return (error_parser(\
		"minishell: syntax error near unexpected token `newline'"));
	ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redir_out, \
	ft_lstnew_redir(ft_strdup(cmd[i + 1]), redir_out_2));
	return (1);
}

int	add_redir_out_1(char **cmd, int i)
{
	if (!cmd[i + 1])
		return (error_parser(\
		"minishell: syntax error near unexpected token `newline'"));
	ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redir_out, \
	ft_lstnew_redir(ft_strdup(cmd[i + 1]), redir_out_1));
	return (1);
}

int	add_redir_in_1(char **cmd, int i)
{
	if (!cmd[i + 1])
		return (error_parser(\
		"minishell: syntax error near unexpected token `newline'"));
	ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redir_in, \
	ft_lstnew_redir(ft_strdup(cmd[i + 1]), redir_in_1));
	return (1);
}

void	redir(char **cmd, int i)
{
	while (cmd[++i])
	{
		if (ft_strncmp(cmd[i], "<<", 2) == 0 && ft_strlen(cmd[i]) == 2)
			add_redir_in_2(cmd, i);
		else if (ft_strncmp(cmd[i], ">>", 2) == 0 && ft_strlen(cmd[i]) == 2)
			add_redir_out_2(cmd, i);
		else if (ft_strncmp(cmd[i], ">", 1) == 0 && ft_strlen(cmd[i]) == 1)
			add_redir_out_1(cmd, i);
		else if (ft_strncmp(cmd[i], "<", 1) == 0 && ft_strlen(cmd[i]) == 1)
			add_redir_in_1(cmd, i);
	}
}
