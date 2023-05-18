#include "minishell.h"

int	heredoc(t_blocks *blocks)
{
	t_blocks	*tmp;
	t_redir	*tmp_redir;
	char	*line;
	int	pid;
	int	status;

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
					signal(SIGINT, signal_heredoc);
					close(blocks->redir->pipe_heredoc[0]);
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
						if (ft_strncmp(line, blocks->redir->file, ft_strlen(blocks->redir->file)) == 0)
						{
							free(line);
							lst_clear_blocks(&tmp);
							exit(0);
						}
						ft_putstr_fd(line, blocks->redir->pipe_heredoc[1]);
						free(line);
					}
					exit(0);
				}
				else
				{
					close(blocks->redir->pipe_heredoc[1]);
					waitpid(pid, &status, 0);
					if (WIFEXITED(status))
					{
						if (WEXITSTATUS(status) == 0)
						{
							close(blocks->redir->pipe_heredoc[1]);
						}
						else
						{
							global_exit_status(WEXITSTATUS(status));
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
