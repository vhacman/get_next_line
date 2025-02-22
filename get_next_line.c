/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_extracted_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:56:15 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/22 16:56:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Takes a string as input and returns its first line (until '\n' or end).
** Modifies input string by removing extracted line from the beginning.
** Returns NULL if input is invalid or malloc fails.
** Line returned includes '\n' if present. */
char	*extract_line(char *raw_input)
{
	char	*line;
	char	*end;
	size_t	len;
	size_t	i;

	if (!raw_input || raw_input[i] == '\0')
		return (NULL);
	end = ft_strchr(raw_input, '\n');
	if (end)
		len = end - raw_input + 1;
	else
		len = ft_strlen(raw_input);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
		line[i] = raw_input[i++];
	line[i] = '\0';
	i = 0;
	if (end)
		while (end[1 + i])
			raw_input[i] = end[1 + i++];
	raw_input[i] = '\0';
	return (line);
}

/*The function reads up to raw_raw_input_SIZE bytes from a file descriptor,
appends them to an existing raw_input string (if present),
and returns the updated string. If there is no data to read,
it returns the original string. If the raw_input string is NULL, 
it returns the data read directly.*/
char	*read_and_update(int fd, char *raw_input_data)
{
	char	*raw_raw_input;
	char	*updated_data;
	int	bytes_read;
	
	raw_raw_input = malloc(sizeof(char) * (raw_raw_input_SIZE + 1));
	if (!raw_raw_input)
		return (NULL);
	bytes_read = read(fd, raw_raw_input, raw_raw_input_SIZE);
	if (bytes_read <= 0)
	{
		free(raw_raw_input);
		return (raw_input_data);
	}
	raw_raw_input[bytes_read] = '\0';
	if (!raw_input_data)
		return (raw_raw_input);
	updated_data = ft_strjoin(raw_input_data, raw_raw_input);
	free (raw_raw_input);
	free (raw_input_data);
	return (updated_data);
}
/* TODO:
* - Read one extracted_line at a time from fd (including STDIN)
* - extracted_lines end with \n (except possible last extracted_line)
* - Handle any file size
* - Preserve data between calls for split extracted_lines
* 
* Implementation tasks:
* 1. Read fd in raw_raw_input_SIZE chunks
* 2. Accumulate data for split extracted_lines
* 3. Extract complete extracted_line
* 4. Return extracted_line & store remainder
* 5. Handle EOF/errors */
char   *get_next_extracted_line( fd)
{
	static char   *raw_input_data;
	char          *stored_data;

	if (fd < 0 || raw_raw_input_SIZE <= 0)
		return (NULL);
	raw_input_data = read_and_update(fd, raw_input_data);
	if (!raw_input_data)
		return (NULL);
	stored_data = extract_extracted_line(raw_input_data);
	raw_input_data = ft_strdup(raw_input_data + ft_strlen(stored_data));
	return (stored_data);
}
