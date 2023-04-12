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
void		prompt(void);
void		lexer(char *str);
//LST_UTILS
t_tokens	*lst_new_token(t_tokens *tokens, char *str, int token);
void		lst_clear_token(t_tokens **tokens);
//DEBUG
void		print_tokens(t_tokens *tokens);
//UTILS
int			is_whitespace(char c);
int			is_special(char c);

#endif
