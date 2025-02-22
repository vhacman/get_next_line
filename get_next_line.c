/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:05:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/22 19:05:39 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (len + 1 == 0)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	ft_strcpy(s2, s1);
	return (s2);
}
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

	i = 0;
	if (!raw_input || raw_input[i] == '\0')
		return (NULL);
	end = ft_strchr(raw_input, '\n');
	if (end)
		len = end - raw_input + 1;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = raw_input[i];
		i++;
	}
	line[i] = '\0';
	i = 0;
	if (end)
		while (raw_input[++i + (end - raw_input)])
			raw_input[i - 1] = raw_input[i + (end - raw_input)];
	raw_input[i - 1] = '\0';
	return (line);
}

/*The function reads up to raw_raw_input_SIZE bytes from a file descriptor,
appends them to an existing raw_input string (if present),
and returns the updated string. If there is no data to read,
it returns the original string. If the raw_input string is NULL, 
it returns the data read directly.*/
char	*read_and_update(int fd, char *raw_input_data)
{
	char	*raw_input;
	char	*updated_data;
	int		bytes_read;

	raw_input = malloc(BUFFER_SIZE + 1);
	if (!raw_input)
		return (free(raw_input_data), NULL);
	bytes_read = read(fd, raw_input, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(raw_input);
		free(raw_input_data);
		return (NULL);
	}
	if (bytes_read == 0)
		return (free(raw_input), raw_input_data);
	raw_input[bytes_read] = '\0';
	if (!raw_input_data)
		return (raw_input);
	updated_data = ft_strjoin(raw_input_data, raw_input);
	free(raw_input);
	free(raw_input_data);
	return (updated_data);
}

char	*read_buffer(int fd, char *raw_input_data)
{
	char	*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = read_and_update(fd, raw_input_data);
	if (!temp)
	{
		free(raw_input_data);
		return (NULL);
	}
	return (temp);
}

char   *get_next_line(int fd)
{
	static char	*raw_input_data;
	char		*stored_data;
	char		*temp;
		
	while (!raw_input_data || !ft_strchr(raw_input_data, '\n'))
	{
		temp = read_buffer(fd, raw_input_data);
		if (!temp)
			return (NULL);
		raw_input_data = temp;
		if (!ft_strchr(raw_input_data, '\n')
			&& ft_strlen(raw_input_data) < BUFFER_SIZE)
			break;
	}
	stored_data = extract_line(raw_input_data);
	if (!stored_data)
	{
		free(raw_input_data);
		raw_input_data = NULL;
		return (NULL);
	}
	temp = ft_strdup(raw_input_data + ft_strlen(stored_data));
	free (raw_input_data);
	raw_input_data = temp;
	return (stored_data);
}
