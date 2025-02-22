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
/* Include delle librerie standard necessarie per:
   - <stdio.h>: Funzioni di input/output come printf.
   - <stddef.h>: Definizioni di tipi fondamentali come NULL e size_t.
   - <stdlib.h>: Funzioni di gestione della memoria come malloc e free.
   - <unistd.h>: Funzione di lettura dei file descriptor come read.
   - <fcntl.h>: Funzioni per la gestione dei file, come open().
   Macro definita per il BUFFER_SIZE, utilizzata per determinare la dimensione
   del buffer da utilizzare durante la lettura dei dati da un file. Se non è 
   già definita in precedenza, viene assegnato un valore di 1000 byte. */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h> 
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char const *string_1, char const *string_2);
char   *get_next_line(int fd);
char	*read_and_update(int fd, char *input_data);
char	*extract_line(char *raw_input);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s1);
char	*read_buffer(int fd, char *raw_input_data);
int   main();
#endif