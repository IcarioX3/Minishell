#ifndef MINISHELL_H
# define MINISHELL_H

//---LIBRARIES---
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"

//---ENUMS---
//PIPE=1, WORD=2, DOLLAR=3, IN_REDIR=4, OUT_REDIR=5, 
//HEREDOC=6, APPEND=7, S_QUOTE=8, D_QUOTE=9, SEP=10

typedef enum e_token
{
	PIPE,
	WORD,
	DOLLAR,
	IN_REDIR,
	OUT_REDIR,
	HEREDOC,
	APPEND,
	S_QUOTE,
	D_QUOTE,
	SEP
}	t_etoken;

//---STRUCTS---

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_tokens
{
	char			*str;
	int				token;
	struct s_tokens	*next;
	struct s_tokens	*previous;
}	t_tokens;

typedef struct s_redir
{
	char			*file;
	int				token;
	struct s_redir	*next;
}	t_redir;

typedef struct s_blocks
{
	char			**cmd;
	int				fd_in;
	int				fd_out;
	int				nb_args;
	t_redir			*redir;
	struct s_blocks	*next;
}	t_blocks;

//---FUNCTIONS---

// ----------------------------------------------------
//	PARSING
// ----------------------------------------------------
int			prompt(void);
t_tokens	*lexer(char *str, t_tokens *tokens);
t_tokens	*parser(t_tokens *tokens, int *exit_status);
t_tokens	*s_quote_parser(t_tokens *tokens);
t_tokens	*d_quote_parser(t_tokens *tokens);
t_tokens	*env_var_parser(t_tokens *tokens, int in_quote);
t_tokens	*redir_parser(t_tokens *tokens);
t_tokens	*split_dollar(t_tokens *tokens);
int			check_close_quote(t_tokens *tokens);
int			check_redir(t_tokens *tokens);
t_blocks	*put_in_blocks(t_blocks *blocks, t_tokens *tokens, int *g_status);
t_redir		*get_redir(t_tokens *tokens);
// ----------------------------------------------------
//	LIST_UTILS
// ----------------------------------------------------
t_tokens	*lst_new_token(t_tokens *tokens, char *str, int token);
void		lst_clear_token(t_tokens **tokens);
t_tokens	*del_token(t_tokens *tokens, t_tokens *tmp);
t_tokens	*insert_token(t_tokens *tmp, char *s, int token);
void		lst_clear_blocks(t_blocks **blocks);
void		lst_clear_redir(t_redir **redir);
// ----------------------------------------------------
//	DEBUG
// ----------------------------------------------------
void		print_tokens(t_tokens *tokens);
void		print_blocks(t_blocks *blocks);
// ----------------------------------------------------
//	UTILS
// ----------------------------------------------------
int			is_whitespace(char c);
int			is_special(char c);
void		free_double_array(char **array);
// ----------------------------------------------------
//	ERROR
// ----------------------------------------------------
void		error_exit(char *str, int exit_code);
void		print_error(char *str);
// ----------------------------------------------------
//	SIGNAL
// ----------------------------------------------------
void		handle_sigint(int sig);
// ----------------------------------------------------
//	BUILTIN
// ----------------------------------------------------
/*echo.c*/
int			ft_nflag(char *input);
void		ft_echo(char **input);
/*cd.c*/
void		ft_cd(char **input);
/*pwd.c*/
int			ft_pwd(char **input);
/*env.c*/
void		ft_env(char **input, t_env **env);
/*export.c*/
int			ft_check_export(char *input, t_env *env);
int			ft_export(char **input, t_env **env);
/*unset.c*/
void		del_env(t_env **remove);
void		ft_check_unset(char *input, t_env **env);
void		ft_unset(char **input, t_env **env);
/*utils_builtin.c*/
void		lst_clear_env(t_env *envi);
t_env		*ft_lstlast_env(t_env *env);
t_env		*ft_lstadd_back_env(t_env *env, t_env *new);
t_env		*lst_new_env_null(t_env *envi, char *str);
t_env		*lst_new_env(t_env *envi, char *str);
t_env		*lst_env(char **env);
/*builtin.c*/
int			check_builtin(char **input, t_env **env);

#endif
