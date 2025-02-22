/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:10:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/22 16:10:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  ft_strlen(const char *str)
{
        int     i;

        i = 0;
        if (!str)
                return (0);
        while (str[i])
                i++;
        return (i);
}

/* la funzione cerca la prima occorrenza del carattere 'c'
 nella strina 'str'. Confronta i caratteri con il carattere
 cercato, se lo trova ritorna un puntatore al carattere trovato,
 se non corrisponde allora passa al carattere successivo.
 Se il carattere trovato è quello di fine stringa,
 restituisce un puntatore al termine della stringa*/
char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *string_1, char const *string_2)
{
	size_t	i;
	size_t	j;
        size_t  len_1;
        size_t  len_2;
	char	*new_str;

	if (!string_1 || !string_2)
		return (NULL);
        len_1 = ft_strlen(string_1);
        len_2 = ft_strlen(string_2);
	new_str = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (string_1[i])
		new_str[j++] = string_1[i++];
	i = 0;
	while (string_2[i])
	        new_str[j++] = string_2[i++];
	new_str[j] = '\0';
	return (new_str);
}
