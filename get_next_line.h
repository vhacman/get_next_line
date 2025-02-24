/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:38:26 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/22 16:38:26 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	   *get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	   *ft_strchr(const char *str, int c);
char	   *ft_strdup(const char *s1);
char	   *ft_strjoin(char const *string_1, char const *string_2);
char	   *ft_strncpy(char *dest, const char *src, unsigned int n);

#endif