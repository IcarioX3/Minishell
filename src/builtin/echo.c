#include "minishell.h"

int	ft_nflag(char *input)
{
	int i;
	int len;

	i = 1;
	len = 0;
	if (!input)
		return (0);
	if (input[0] != '-')
		return (0);
	while (input[len])
		len++;
	while (input[i] == 'n')
		i++;
	if (len == 1)
		printf("%s\n", input);
	if (i == len)
		return (1);
	else
		return (0);
}

void	ft_echo(char **input)
{
	int i = 1;
	int nflag = 0;

	if (ft_strlen(input[0]) == 4)
	{
		if (ft_strnstr(input[0], "echo", 4) != NULL)
		{
			if (input[1] != NULL && ft_nflag(input[1]) == 1)
			{
				nflag = 1;
				i++;
			}
			while (input[i])
			{
				printf("%s", input[i]);
				i++;
				if (input[i] != NULL) 
					printf(" ");
			}
			if (nflag == 0)
			{
				printf("\n");
			}
		}
	}
}
