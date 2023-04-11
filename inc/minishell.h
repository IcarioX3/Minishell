#ifndef MINISHELL_H
# define MINISHELL_H

//INCLUDES
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft.h"

//ENUMS
typedef	enum e_token
{
	PIPE,
	WORD,
	DOLLAR,
	IN_REDIR,
	OUT_REDIR,
	IN_HEREDOC,
	OUT_HEREDOC,
	S_QUOTE,
	D_QUOTE,
	SEP
}	t_etoken;

//STRUCTS
typedef	struct s_lexer
{
	char	*str;
	int		token;
	struct s_lexer	*next;
	struct s_lexer	*previous;
}	t_lexer;

//FUNCTIONS
void	prompt(void);

#endif
