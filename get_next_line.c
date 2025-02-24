/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:20:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/24 23:00:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Takes a string as input and returns its first line (until '\n' or end).
** Modifies input string by removing extracted line from the beginning.
** Returns NULL if input is invalid or malloc fails.
** Line returned includes '\n' if present. */
char	*extract_line(char **raw_input_ptr)
{
	char		*line;
	t_line_data	data;
	size_t		line_len;

	if (!raw_input_ptr || !*raw_input_ptr || !**raw_input_ptr)
		return (NULL);
	data.raw_input = *raw_input_ptr;
	data.raw_input_ptr = raw_input_ptr;
	data.end = ft_strchr(data.raw_input, '\n');
	data.remainder = NULL;
	if (data.end)
		line_len = data.end - data.raw_input + 1;
	else
		line_len = ft_strlen(data.raw_input);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	ft_strncpy(line, data.raw_input, line_len);
	line[line_len] = '\0';
	extract_line_helper(data, line);
	return (line);
}

/* Function to handle cleanup after extracting line */
void	extract_line_helper(t_line_data data, char *line)
{
	if (data.end && *(data.end + 1))
	{
		data.remainder = ft_strdup(data.end + 1);
		if (!data.remainder)
			free(line);
		free(data.raw_input);
		*(data.raw_input_ptr) = data.remainder;
	}
	else
	{
		free(data.raw_input);
		*(data.raw_input_ptr) = NULL;
	}
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
		return (free(buffer), NULL);
	if (bytes_read == 0)
		return (free(buffer), raw_input_data);
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

char	*get_next_line_reader(int fd, char *raw_input_data)
{
	char	*read_done;

	while (!raw_input_data || !ft_strchr(raw_input_data, '\n'))
	{
		read_done = read_and_update(fd, raw_input_data);
		if (!read_done)
		{
			if (raw_input_data)
				free(raw_input_data);
			raw_input_data = NULL;
			return (NULL);
		}
		if (read_done == raw_input_data
			&& !ft_strchr(raw_input_data, '\n'))
			break ;
		raw_input_data = read_done;
	}
	return (raw_input_data);
}

char	*get_next_line(int fd)
{
	static char	*raw_input_data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	raw_input_data = get_next_line_reader(fd, raw_input_data);
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
