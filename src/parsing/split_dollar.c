#include "minishell.h"

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (is_whitespace(str[i]))
			i++;
		else
		{
			count++;
			while (str[i] && !is_whitespace(str[i]))
				i++;
		}
	}
	return (count);
}

char	**get_split_str(char *str)
{
	char	**split;
	int		i;
	int		j;
	int		k;

	split = malloc((count_words(str) + 1) * sizeof(char *));
	if (count_words(str) == 0 || !split)
		return (NULL);
	i = -1;
	j = 0;
	k = -1;
	while (++i <= ft_strlen(str))
	{
		if (is_whitespace(str[i]) && k < 0)
			continue ;
		else if ((is_whitespace(str[i]) || str[i] == '\0') && k >= 0)
		{
			split[j++] = ft_substr(str, k, i - k);
			k = -1;
		}
		else if (!is_whitespace(str[i]) && k < 0)
			k = i;
	}
	split[j] = NULL;
	return (split);
}

t_tokens	*split_dollar(t_tokens *tokens)
{
	t_tokens	*tmp;
	char		**split;
	int			i;

	tmp = tokens;
	if (!tmp || !tmp->str)
		return (tokens);
	split = get_split_str(tmp->str);
	if (!split)
		return (NULL);
	i = count_words(tmp->str);
	free(tmp->str);
	tmp->str = split[0];
	tmp->token = DOLLAR;
	if (i > 1)
	{
		i = 1;
		while (split[i])
		{
			tmp = insert_token(tmp, split[i], DOLLAR);
			i++;
		}
	}
	free(split);
	return (tokens);
}
