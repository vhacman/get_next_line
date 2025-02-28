/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:20:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/24 21:21:11 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1 -> for printf, BUFFER_SIZE
2 -> for size_t, sizeof()
3 -> for open(), read()
4 -> for malloc(), free()
5 -> for ssize_t
6 -> for O_RDONLY
*/
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer_info
{
	char	*end;
	char	*remainder;
	char	*raw_input;
	char	**raw_input_ptr;
}	t_buffer_info;

char		*get_next_line(int fd);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *string_1, char const *string_2);
char		*ft_strncpy(char *dest, const char *src, unsigned int n);
void		extract_line_helper(t_buffer_info data, char *line);
char		*get_next_line_reader(int fd, char *raw_input_data);

//int			main(void);

#endif