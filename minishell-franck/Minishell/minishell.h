/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franck <franck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 01:32:45 by nbled             #+#    #+#             */
/*   Updated: 2023/04/11 14:11:43 by franck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED     "\x1b[31;1m"
# define GREEN   "\x1b[32;1m"
# define YELLOW  "\x1b[33;1m"
# define BLUE    "\x1b[34;1m"
# define MAGENTA "\x1b[35;1m"
# define CYAN    "\x1b[36;1m"
# define END    "\x1b[0m"

# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>

typedef struct s_pile
{
	int 			value;
	int				token;
	char			*str;
	struct s_pile	*prev;
	struct s_pile	*next;
}					t_pile;

typedef enum token
{
	WORD,
	PIPE,
	LFT_RDIR,
	RGT_RDIR,
	RGT_HRDC,
	LFT_HRDC,
	FLE,
	CMD,
} 	e_token;


// ----------------------------------------------------
//	LIST
// ----------------------------------------------------

t_pile	*ft_lstnew(int value, char *str);
t_pile	*ft_lstlast(t_pile *pile);
size_t	ft_lstsize(t_pile *pile);
void	ft_lstadd_back(t_pile **pile, t_pile *n);
void	ft_lstclear(t_pile *start);

// ----------------------------------------------------
//	SPLIT
// ----------------------------------------------------

size_t	ft_count_words(const char *s);
size_t	ft_str_len(char const *s);
char	**ft_split(const char *s);
int		isasep(const char c);

// ----------------------------------------------------
//	TOKEN.C
// ----------------------------------------------------

void	get_token_sign(t_pile *start);
int	get_token(t_pile *start);

// ----------------------------------------------------
//	UTILS.C
// ----------------------------------------------------

size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strstr(char *str, char *to_find);

// ----------------------------------------------------
//	UTILS.C
// ----------------------------------------------------

void	check_pwd(t_pile *start);
void	check_env(t_pile *start, char **env);
void	check_echo(t_pile *start);
void	check_builtin(t_pile *start, char **env);

// ----------------------------------------------------
//	OTHER
// ----------------------------------------------------

int		quote_check(char *str);

#endif
