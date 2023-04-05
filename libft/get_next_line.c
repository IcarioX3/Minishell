/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:16:15 by icario            #+#    #+#             */
/*   Updated: 2023/01/23 18:35:32 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	s = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!s || !s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		s[j] = s2[i];
		i++;
		j++;
	}
	free(s1);
	s[j] = '\0';
	return (s);
}

char	*read_file(char *stash, char *buff, int fd)
{
	int	bite_read;

	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	if (!stash)
		return (NULL);
	bite_read = 1;
	while (bite_read > 0)
	{
		bite_read = read(fd, buff, BUFFER_SIZE);
		if (bite_read <= 0 && stash[0] == '\0')
		{
			free(stash);
			return (NULL);
		}
		buff[bite_read] = '\0';
		stash = ft_strjoin_gnl(stash, buff);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

char	*next_line(char *stash)
{
	char	*next_line;
	int		i;
	int		j;
	int		end_file;

	i = 0;
	end_file = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (ft_strchr(stash, '\n'))
		end_file = 1;
	next_line = ft_calloc(i + 1 + end_file, sizeof(char));
	if (!next_line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		next_line[j] = stash[j];
		j++;
	}
	next_line[j] = '\n';
	next_line[j + end_file] = '\0';
	return (next_line);
}

char	*new_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	new_stash = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i++])
		new_stash[j++] = stash[i];
	free(stash);
	new_stash[j] = '\0';
	if (new_stash[0] == '\0')
		return (free(new_stash), NULL);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*stash;
	char		*line;

	if (fd > 1048576 || fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	stash = read_file(stash, buff, fd);
	if (!stash)
		return (NULL);
	line = next_line(stash);
	stash = new_stash(stash);
	return (line);
}
/*
int	main(void)
{
	int	fd;
	char	*line;

	fd = open("../maps/test.ber",O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
}
*/