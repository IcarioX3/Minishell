/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:48 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:32:19 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_blocks	*parsing(t_blocks *blocks, char *input, t_env **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	tokens = lexer(input, tokens);
	free(input);
	tokens = parser(tokens, env);
	if (return_global_exit_status() != 0)
		return (lst_clear_token(&tokens), NULL);
	blocks = put_in_blocks(blocks, tokens);
	if (!blocks)
	{
		lst_clear_token(&tokens);
		lst_clear_blocks(&blocks);
		return (NULL);
	}
	lst_clear_token(&tokens);
	return (blocks);
}

void	handle_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

void	execution(char *input, t_env **envi, t_blocks *blocks)
{
	while (1)
	{
		input = readline("\033[36mminishell$\033[0m ");
		add_history(input);
		if (!input || input[0] == '\0')
		{
			free(input);
			if (!input)
			{
				printf("exit\n");
				break ;
			}
			continue ;
		}
		blocks = parsing(blocks, input, envi);
		if (!blocks)
			continue ;
		if (exec(blocks, *envi, envi) == 1)
		{
			lst_clear_blocks(&blocks);
			break ;
		}
		lst_clear_blocks(&blocks);
		handle_signal();
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_blocks	*blocks;
	t_env		*envi;

	(void)argv;
	envi = NULL;
	blocks = NULL;
	input = NULL;
	if (argc != 1)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	envi = lst_env(env);
	if (!envi)
		return (1);
	execution(input, &envi, blocks);
	if (envi)
		lst_clear_env(envi);
	return (0);
}
