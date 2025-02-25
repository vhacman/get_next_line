/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:26:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/25 12:51:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* extract_line - Estrae una singola riga da un buffer di input grezzo
 * Questa funzione estrae una riga (fino al carattere newline incluso,
 * se presente) dal buffer di input fornito. Restituisce la riga estratta
 * come una nuova stringa allocata e aggiorna il puntatore del buffer originale
 * per puntare ai dati rimanenti.
 * Parametri:
 *   raw_input_ptr: Puntatore a un puntatore al buffer di input grezzo.
 * Verrà aggiornato per puntare alla riga successiva dopo l'estrazione.
 * Valore di ritorno:
 *   Una stringa appena allocata contenente la riga estratta, o NULL se:
 *   - I parametri di input non sono validi (puntatore NULL)
 *   - Il buffer di input è vuoto
 *   - L'allocazione di memoria fallisce
 */
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

/* extract_line_helper - Funzione ausiliaria per gestire il buffer 
  dopo l'estrazione di una riga  * Questa funzione gestisce
  la pulizia e l'aggiornamento del buffer di input dopo che 
  una riga è stata estratta. Si occupa di gestire il testo rimanente, 
  liberare il buffer originale e aggiornare il puntatore.  */
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

/* read_and_update - Legge dati da un file descriptor e
  aggiorna il buffer di input  * Questa funzione legge un blocco di 
  dati dal file descriptor specificato
 * e lo aggiunge al buffer di input esistente (se presente).
 */
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

/* get_next_line_reader - Legge dati da un file descriptor fino 
 a trovare un newline o EOF  * Questa funzione legge dati dal
 file descriptor specificato fino a quando non viene trovato
 * un carattere newline ('\n') o viene raggiunta la fine del file (EOF).
 */
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

/* get_next_line - Legge una riga da un file descriptor
 * Questa funzione legge una riga da un file descriptor specificato e la
 * restituisce come una stringa terminata da null. Ad ogni chiamata successiva
 * con lo stesso file descriptor, restituisce la riga successiva.
 * Versione bonus che supporta la lettura da più file descriptor 
 contemporaneamente  * utilizzando un array di buffer per 
 mantenere lo stato di ciascun FD.
 * Parametri:
 *   fd: File descriptor da cui leggere
 * Valore di ritorno:
 *   Una stringa contenente la riga letta, o NULL se:
 *   - Il parametro fd è invalido (negativo o >= OPEN_MAX)
 *   - BUFFER_SIZE è impostato a un valore non positivo
 *   - La fine del file è stata raggiunta e non ci sono più dati da leggere
 *   - Si è verificato un errore durante la lettura */
char	*get_next_line(int fd)
{
	static char	*fd_buffers[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	fd_buffers[fd] = get_next_line_reader(fd, fd_buffers[fd]);
	if (!fd_buffers[fd] || !*fd_buffers[fd])
	{
		if (fd_buffers[fd])
		{
			free(fd_buffers[fd]);
			fd_buffers[fd] = NULL;
		}
		return (NULL);
	}
	line = extract_line(&fd_buffers[fd]);
	return (line);
}

// int main(void)
// {
//     int     fd1;
//     int     fd2;
//     int     fd3;
//     char    *line;

//		fd1 = open("file1.txt", O_RDONLY);
//		fd2 = open("file2.txt", O_RDONLY);
//		fd3 = open("file3.txt", O_RDONLY);
//		if (fd1 == -1 || fd2 == -1 || fd3 == -1)
//     {
//         printf("Errore nell'apertura dei file\n");
//         return (1);
//     }
//		line = get_next_line(fd1);
//		printf("File 1: %s", line);
//		ree(line);
//		line = get_next_line(fd2);
//		printf("File 2: %s", line);
//		free(line);
//		line = get_next_line(fd3);
//		printf("File 3: %s", line);
//		free(line);
//		line = get_next_line(fd1);
//		printf("File 1: %s", line);
//		free(line);
//		close(fd1);
//		close(fd2);
//		close(fd3);
//     return (0);
// }
