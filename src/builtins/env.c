/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:05:32 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:43:43 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	memclean(char **s, size_t l)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (i < l)
		{
			free (s[i]);
			i++;
		}
		free (s);
	}
}

void	print_env_list(t_env_list *env_list, int flag)
{
	while (env_list)
	{
		if (EXPORT_MODE == flag)
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (!env_list->equal && ENV_MODE == flag)
		{
			env_list = env_list->next;
			continue ;
		}
		ft_putstr_fd(env_list->key, 1);
		if (env_list->equal)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			if (EXPORT_MODE == flag)
				ft_putchar_fd('\"', STDOUT_FILENO);
			if (env_list->val)
				ft_putstr_fd(env_list->val, STDOUT_FILENO);
			if (EXPORT_MODE == flag)
				ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putendl_fd("", STDOUT_FILENO);
		env_list = env_list->next;
	}
}

char	*get_env(char *key, t_env_list *env_list)
{
	while (env_list)
	{
		if (!ft_strcmp(key, env_list->key) && env_list->equal)
			return (env_list->val);
		env_list = env_list->next;
	}
	return (NULL);
}

void	env(void)
{
	g_shell.status = 0;
	print_env_list(g_shell.env_list, ENV_MODE);
}
