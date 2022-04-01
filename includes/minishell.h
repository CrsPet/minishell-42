#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include <wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "../libft/libft.h"
#include "parser.h"

typedef struct s_env_store
{
	char				*key;
	char				*val;
	int					equal;
	// struct s_env_store	*next;
}				t_env_store;

typedef struct s_env_list
{
	char				*key;
	char				*val;
	int					equal;
	struct s_env_list	*next;
}				t_env_list;
typedef struct s_minishell
{
	int				stdin;
	int				stdout;
	char			**env;
	int				status;
	int				env_changed;
	void			*temp;
	int				**fds;
	int				fd_write;
	int				fd_read;
	pid_t			*pids;
	t_env_list		*env_list;
	struct s_cmd	*cmd_list;
	struct s_cmd	*cmd_list_head;
}				t_minishell;


//typedef struct s_cmd
//{
//	int				f1;
//	int				f2;
//	int				pipe_in;
//	int				pipe_out;
//	int				redir_in;
//	int				redir_out;
//	char			**args;
//	char			*limiter;
//	t_minishell		*mshell;
//	struct s_cmd	*next;
//}				t_cmd;

typedef enum e_stat
{
	default_pipe_in,
	default_pipe_out,
	pipe_in,
	pipe_out,
	redir_in_1,
	redir_in_2,
	redir_out_1,
	redir_out_2
}					t_stat;

typedef struct s_redir
{
	int					type_redr;
	char				*filename;
	struct s_redir		*next;
}				t_redir;

typedef struct s_cmd
{
	char			**args;
	int				pipe_in;
	int				pipe_out;
	t_redir			*redir_in;
	t_redir			*redir_out;
	struct s_cmd	*next;
}				t_cmd;

void	clear_all(t_minishell *shell);
void	cmd_end_works(int **fds, pid_t *pids, int i);
void	change_shlvl(void);
t_env_list	*cp_env(t_env_list *env_list);
int			valid_export(char *arg);
int			ft_strcmp(char const *s1, char const *s2);
t_env_list	*sort_env_list(t_env_list *start);
int		open_redirs(t_cmd *cmd_list);
void	close_fds(int	**fds);
void	print_error(char *arg, char *err_name);
int		file_check(char *file_path, int mode);
void	print_export(t_env_list *env_list);
int			len_env_list(int mode, t_env_list *env_list);
t_env_list	*lst_envnew(char *key, char *val);
t_env_list	*lst_envlast(t_env_list *lst);
void		lst_envadd_back(t_env_list **list, t_env_list *new);
void		clean_env_list(t_env_list *list);
void		get_env_list(t_env_list **env_list, char **envp);
void	print_env_list(t_env_list *env_list, int flag);
t_env_list	*get_env_elem(char *input);
void	del_lst_env_elem(t_env_list *env_list);
void	lst_env_pop(t_env_list **list, char *key);
void	lst_envadd_front(t_env_list **lst, t_env_list *new);

int		is_builtin(char *arg);
void	exit_with_error(char *str);
int		get_pids_fds(t_cmd *cmd_list);
int		check_atoi(char *str);
void	clean_cmd_list(t_cmd *cmd_list);
void	ft_exit(char **args);
int		set_redir_in(t_redir *redir);
int		set_redir_out(t_redir *redir);
void	*parser(char *str, char **envp);
char	*ft_dollar(char *str, int *i, char **envp);
char	*ft_quotes(char *str, int *i);
char	*ft_quotes_2(char *str, int *i, char **envp);
void	signal_init();
char 	*pipe_parse(int *i,char *str, char **envp);
char	*correct_str(char *str, char **envp);
int		prepars(const char *str);
t_cmd	*ft_lstnew_parse(void *content);
t_cmd	*ft_lstlast_parse(t_cmd *lst);
t_redir	*ft_lstlast_redir(t_redir *lst);
t_redir	*ft_lstnew_redir(void *content, int type);
void	ft_lstadd_back_parse(t_cmd **lst, t_cmd *new);
void	ft_lstadd_back_redir(t_redir **lst, t_redir *new);
char 	*right_redirect(char *str, int *i, char **envp);
char *left_redirect(char *str, int *i, char **envp);
void redir(char **cmd);
void error_parser(char *cmd);

t_redir	*lst_redirlast(t_redir *lst);
void	lst_rediradd_back(t_redir **redir, t_redir *new);
t_redir	*lst_redirnew(char *file, int type);

void	change_env_val(char *input, t_env_list **env_list);
void	export(t_env_list **env_list, char **args);
int		len_2d_str(char **str);
void	env(char **args, t_env_list *env_list);
void	pwd(int fd);
void	change_dir();
void	echo(char **args);
void	unset(char **args, t_env_list **env_list);
int		exec();
char	**cp_2d_arr(char **envp);
int		get_ind_env(char *point, char **envp);
void	memclean(char **s, size_t l);
char	*get_env(char *key, t_env_list *env_list);
void	initialisation(char **envp);
int	work_here_doc(char *limiter, int *f);

char	*collect_str_env (t_env_list *elem);
char	**collect_env(t_env_list *env_list);
void	print_env_store(t_env_store *env_store, int fd);
char	*get_key(char *var);
int		parse_cmds(t_cmd *cmd);
int		ft_strcmp(char const *s1, char const *s2);
void	lst_cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*lst_cmdnew(t_minishell *mshell);
t_cmd	*lst_cmdlast(t_cmd *lst);
t_minishell	shell;
#endif