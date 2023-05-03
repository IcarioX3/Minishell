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

//---FUNCTIONS---

// ----------------------------------------------------
//	PARSING
// ----------------------------------------------------
int			prompt(void);
t_tokens	*lexer(char *str, t_tokens *tokens);
void		parser(t_tokens **tokens);
t_tokens	*s_quote_parser(t_tokens *tokens);
t_tokens	*d_quote_parser(t_tokens *tokens);
t_tokens	*env_var_parser(t_tokens *tokens, int in_quote);
// ----------------------------------------------------
//	LIST_UTILS
// ----------------------------------------------------
t_tokens	*lst_new_token(t_tokens *tokens, char *str, int token);
void		lst_clear_token(t_tokens **tokens);
t_tokens	*del_token(t_tokens *tokens, t_tokens *tmp);
// ----------------------------------------------------
//	DEBUG
// ----------------------------------------------------
void		print_tokens(t_tokens *tokens);
// ----------------------------------------------------
//	UTILS
// ----------------------------------------------------
int			is_whitespace(char c);
int			is_special(char c);
void	free_split(char **args);
// ----------------------------------------------------
//	ERROR
// ----------------------------------------------------
void		error_exit(char *str, int exit_code);
void		print_error(char *str);
// ----------------------------------------------------
//	SIGNAL
// ----------------------------------------------------
void	handle_sigint(int sig);
// ----------------------------------------------------
//	BUILTIN
// ----------------------------------------------------
/*echo.c*/
int	ft_nflag(char *input);
void	ft_echo(char **input);
/*cd.c*/
void	ft_cd(char **input);
/*pwd.c*/
int	ft_pwd(char **input);
/*env.c*/
void	ft_env(char **input, t_env **env);
/*export.c*/
void	ft_check_export(char *input, t_env *env);
void	ft_export(char **input, t_env **env);
/*unset.c*/
void del_env(t_env **remove);
void	ft_check_unset(char *input, t_env **env);
void	ft_unset(char **input, t_env **env);
/*utils_builtin.c*/
void	lst_clear_env(t_env *envi);
t_env	*ft_lstlast_env(t_env *env);
t_env	*ft_lstadd_back_env(t_env *env, t_env *new);
t_env	*lst_new_env(t_env *envi, char *str);
t_env *lst_env(char **env);
/*builtin.c*/
void	check_builtin(char **input, t_env **env);



#endif
