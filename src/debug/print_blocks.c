/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:15:16 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:15:18 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	print_blocks(t_blocks *blocks)
// {
// 	int			i;
// 	int			j;
// 	t_blocks	*tmp;
// 	t_redir		*tmp_redir;

// 	tmp = blocks;
// 	i = 0;
// 	j = 0;
// 	printf("\nAfter putting blocks:\n");
// 	while (tmp)
// 	{
// 		printf("--------------------\n");
// 		printf("Block %d\n", i);
// 		printf("Command:");
// 		while (tmp->nb_args > j)
// 		{
// 			printf(" \"%s\"", tmp->cmd[j]);
// 			j++;
// 		}
// 		printf("\n");
// 		printf("Redir:\n");
// 		j = 0;
// 		tmp_redir = tmp->redir;
// 		while (tmp_redir)
// 		{
// 			printf("(%d) ", j);
// 			printf("| file: \"%s\" | ", tmp_redir->file);
// 			if (tmp_redir->token == IN_REDIR)
// 				printf("token: IN_REDIR\n");
// 			else if (tmp_redir->token == OUT_REDIR)
// 				printf("token: OUT_REDIR\n");
// 			else if (tmp_redir->token == APPEND)
// 				printf("token: APPEND\n");
// 			else if (tmp_redir->token == HEREDOC)
// 				printf("token: HEREDOC\n");
// 			else
// 				printf("token: %d\n", tmp_redir->token);
// 			tmp_redir = tmp_redir->next;
// 			j++;
// 		}
// 		j = 0;
// 		tmp = tmp->next;
// 		i++;
// 	}
// }
