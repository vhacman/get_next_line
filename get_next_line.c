/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 09:00:30 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/24 17:07:30 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Takes a string as input and returns its first line (until '\n' or end).
** Modifies input string by removing extracted line from the beginning.
** Returns NULL if input is invalid or malloc fails.
** Line returned includes '\n' if present. */
char	*extract_line(char **raw_input_ptr)
{
	char	*line;
	char	*end;
	size_t	line_len;
	char	*remainder;
	char	*raw_input;

	if (!raw_input_ptr || !*raw_input_ptr || !**raw_input_ptr)
		return (NULL);
	raw_input = *raw_input_ptr;
	end = ft_strchr(raw_input, '\n');
	if (end)
		line_len = end - raw_input + 1;
	else
		line_len = ft_strlen(raw_input);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	ft_strncpy(line, raw_input, line_len);
	line[line_len] = '\0';
	if (end && *(end + 1))
	{
		remainder = ft_strdup(end + 1);
		if (!remainder)
		{
			free(line);
			return (NULL);
		}
		free(raw_input);
		*raw_input_ptr = remainder;
	}
	else
	{
		free(raw_input);
		*raw_input_ptr = NULL;
	}
	return (line);
}

/* Reads from the file descriptor and appends to the existing buffer.
** Returns the updated buffer or NULL if reading fails or an error occurs.
** Handles proper memory management for both success and error cases. */
char	*read_and_update(int fd, char *raw_input_data)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (bytes_read == 0)
	{
		free(buffer);
		return (raw_input_data);
	}
	buffer[bytes_read] = '\0';
	if (!raw_input_data)
		temp = ft_strdup(buffer);
	else
		temp = ft_strjoin(raw_input_data, buffer);
	free(buffer);
	free(raw_input_data);
	return (temp);
}

/* Main function that reads a line from a file descriptor.
** Returns a line ending with newline if present, otherwise the remaining text.
** Returns NULL at EOF or if an error occurs.
** Uses a static array to handle multiple file descriptors. */
char	*get_next_line(int fd)
{
	static char	*raw_input_data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	if (!raw_input_data || !ft_strchr(raw_input_data, '\n'))
	{
		while (1)
		{
			raw_input_data = read_and_update(fd, raw_input_data);
			if (!raw_input_data)
				return (NULL);
			if (!*raw_input_data)
				break;
			if (ft_strchr(raw_input_data, '\n'))
				break;
		}
	}
	
	if (!raw_input_data || !*raw_input_data)
	{
		if (raw_input_data)
		{
			free(raw_input_data);
			raw_input_data = NULL;
		}
		return (NULL);
	}
	
	line = extract_line(&raw_input_data);
	return (line);
}
