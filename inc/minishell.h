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
	WORD;
	PIPE;
	FILE;
	CMD;
	IN_REDIR;
	OUT_REDIR;
	IN_HEREDOC;
	OUT_HEREDOC;
}	t_token;

//STRUCTS
typedef	struct s_token
{
	char	*str;
	int		token;
}

//FUNCTIONS
void	prompt(void);

#endif
