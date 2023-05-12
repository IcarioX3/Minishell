#include "minishell.h"

int	heredoc(t_blocks *blocks, int *g_status)
{
	t_blocks	*tmp;
	t_redir	*tmp_redir;
	char	*line;
	int	pid;
	int	err_dup;
	int	status;

	err_dup = 0;
	line = NULL;
	tmp = blocks;
	while (blocks)
	{
		tmp_redir = blocks->redir;
		while(blocks->redir)
		{
			if (blocks->redir->token == HEREDOC)
			{
				if (pipe(blocks->redir->pipe_heredoc) == -1)
					return (0);
				pid = fork();
				if (pid == -1)
					return (0);
				if (pid == 0)
				{
					close(blocks->redir->pipe_heredoc[0]);
					err_dup = dup2(blocks->redir->pipe_heredoc[1], 1);
					if (err_dup == -1)
						return (0);
					close(blocks->redir->pipe_heredoc[1]);
					while (1)
					{
						ft_putstr_fd("> ", STDIN_FILENO);
						line = get_next_line(STDIN_FILENO);
						if (!line)
						{
							free(line);
							lst_clear_blocks(&tmp);
							exit(0);
						}
						ft_putstr_fd("file: ", 2);
						ft_putstr_fd(blocks->redir->file, 2);
						ft_putstr_fd("\n", 2);																								
						ft_putstr_fd("line: ", 2);
						ft_putstr_fd(line, 2);
						if (ft_strncmp(line, blocks->redir->file, ft_strlen(blocks->redir->file)) == 0)
						{
							free(line);
							lst_clear_blocks(&tmp);
							exit(0);
						}
						ft_putstr_fd(line, blocks->redir->pipe_heredoc[1]);
						ft_putstr_fd("\n", blocks->redir->pipe_heredoc[1]);
						free(line);
					}
					exit(0);
				}
				else
				{
					ft_putstr_fd("Here\n", 2);
					close(blocks->redir->pipe_heredoc[1]);
					waitpid(pid, &status, 0);
					if (WIFEXITED(status))
					{
						if (WEXITSTATUS(status) == 0)
						{
							err_dup = dup2(blocks->redir->pipe_heredoc[0], 0);
							if (err_dup == -1)
								return (0);
							close(blocks->redir->pipe_heredoc[0]);
						}
						else
						{
							*g_status = WEXITSTATUS(status);
							return (0);
						}
					}
				}
			}
			blocks->redir = blocks->redir->next;
		}
		blocks->redir = tmp_redir;
		blocks = blocks->next;
	}
	blocks = tmp;
	return (1);
}
