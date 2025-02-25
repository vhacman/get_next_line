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
// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error opening file");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (0);
// }