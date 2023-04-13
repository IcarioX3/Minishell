#ifndef MINISHELL_H
# define MINISHELL_H

//---LIBRARIES---
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft.h"

//---ENUMS---
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
typedef struct s_tokens
{
	char			*str;
	int				token;
	struct s_tokens	*next;
	struct s_tokens	*previous;
}	t_tokens;

//---FUNCTIONS---

//PARSING
int			prompt(void);
t_tokens	*lexer(char *str, t_tokens *tokens);
void		parser(t_tokens **tokens);
//LST_UTILS
t_tokens	*lst_new_token(t_tokens *tokens, char *str, int token);
void		lst_clear_token(t_tokens **tokens);
void		lst_delone_token(t_tokens **tokens, t_tokens *del);
//DEBUG
void		print_tokens(t_tokens *tokens);
//UTILS
int			is_whitespace(char c);
int			is_special(char c);
//ERRORS
void		error_exit(char *str, int exit_code);
void		print_error(char *str);

#endif
