#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || (c <= 13 && c >= 9))
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '|' || c == '$' || c == '\'' || c == '\"' || c == '<' || c == '>')
		return (1);
	return (0);
}
