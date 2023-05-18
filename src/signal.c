#include "minishell.h"

int	g_exit_status = 0;

int	return_global_exit_status(void)
{
	return (g_exit_status);
}

int	global_exit_status(int new_value)
{
	g_exit_status = new_value;
	return (return_global_exit_status());
}

void	handle_sigint(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_heredoc(int signal)
{
	printf("\n");
	global_exit_status(130);
	if (signal == SIGINT)
		close(0);
}

void	signal_fork(int signal)
{
	if (signal == SIGINT)
		global_exit_status(130);
	else if (signal == SIGQUIT)
		global_exit_status(131);
	 ft_putstr_fd("exit\n", 1);
}
