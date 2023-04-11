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
	WORD,
	PIPE,
	CMD,
	IN_REDIR,
	OUT_REDIR,
	IN_HEREDOC,
	OUT_HEREDOC
}	t_etoken;

//STRUCTS
typedef	struct s_lexer
{
	char	*str;
	int		token;
}	t_lexer;

//FUNCTIONS
void	prompt(void);

#endif
