#include "minishell.h"

void    error_exit(char *str, int exit_code)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("\n", 2);
    exit(exit_code);
}
