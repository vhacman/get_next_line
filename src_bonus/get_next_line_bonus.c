/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:36:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/11 13:54:29 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	if (!*buffer || !**buffer)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	line = ft_strdup(*buffer);
	line[i] = '\0';
	temp = ft_strdup(*buffer + i);
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*read_to_buffer(int fd, char *buffer)
{
	char	*chunk;
	ssize_t	b_read;

	b_read = 1;
	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (NULL);
	while (b_read > 0 && !ft_strchr(buffer, '\n'))
	{
		b_read = read(fd, chunk, BUFFER_SIZE);
		if (b_read < 0)
		{
			free(chunk);
			free(buffer);
			return (NULL);
		}
		chunk[b_read] = '\0';
		buffer = ft_strjoin(buffer, chunk);
	}
	free(chunk);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*fd_buffers[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	fd_buffers[fd] = read_to_buffer(fd, fd_buffers[fd]);
	if (!fd_buffers[fd])
		return (NULL);
	line = extract_line(&fd_buffers[fd]);
	return (line);
}

// int	main(void)
// {
// 	int		fd1, fd2, fd3;
// 	char	*line1, *line2, *line3;
// 	int		active1, active2, active3;

// 	fd1 = open("file1.txt", O_RDONLY);
// 	fd2 = open("file2.txt", O_RDONLY);
// 	fd3 = open("file3.txt", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
// 	{
// 		printf("Errore nell'apertura dei file\n");
// 		return (1);
// 	}
// 	active1 = active2 = active3 = 1;
// 	while (active1 || active2 || active3)
// 	{
// 		if (active1 && (line1 = get_next_line(fd1)))
// 		{
// 			printf("File 1: %s", line1);
// 			free(line1);
// 		}
// 		else
// 			active1 = 0;
// 		if (active2 && (line2 = get_next_line(fd2)))
// 		{
// 			printf("File 2: %s", line2);
// 			free(line2);
// 		}
// 		else
// 			active2 = 0;
// 		if (active3 && (line3 = get_next_line(fd3)))
// 		{
// 			printf("File 3: %s", line3);
// 			free(line3);
// 		}
// 		else
// 			active3 = 0;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
