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

/* extract_line - Estrae una singola riga da un buffer di input grezzo
 * Questa funzione estrae una riga (fino al carattere newline incluso,
 * se presente) dal buffer di input fornito. Restituisce la riga estratta
 * come una nuova stringa allocata e aggiorna il puntatore del buffer originale
 * per puntare ai dati rimanenti.
 * Parametri:
 *   raw_input_ptr: Puntatore a un puntatore al buffer di input grezzo.
 *                  Verrà aggiornato per puntare alla riga successiva dopo l'estrazione.
 * Valore di ritorno:
 *   Una stringa appena allocata contenente la riga estratta, o NULL se:
 *   - I parametri di input non sono validi (puntatore NULL)
 *   - Il buffer di input è vuoto
 *   - L'allocazione di memoria fallisce
 * Note:
 *   - La funzione gestisce input sia terminati da newline che non terminati da newline
 *     (nel secondo caso viene trattato come l'ultima riga di input)
 *   - Il chiamante è responsabile di liberare la stringa restituita
 *   - La funzione utilizza le funzioni ausiliarie ft_strchr, ft_strlen e ft_strncpy
 *   - La funzione utilizza una funzione ausiliaria extract_line_helper per aggiornare
 *     il raw_input_ptr dopo l'estrazione  */
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

/* extract_line_helper - Funzione ausiliaria per gestire il buffer dopo l'estrazione di una riga
 * Questa funzione gestisce la pulizia e l'aggiornamento del buffer di input dopo che
 * una riga è stata estratta dalla funzione principale extract_line. Si occupa di:
 * - Gestire il testo rimanente dopo la riga estratta
 * - Liberare il buffer originale
 * - Aggiornare il puntatore per puntare ai dati rimanenti o a NULL
 * Parametri:
 *   data: Struttura contenente tutti i dati necessari (puntatori al buffer, posizione
 *         della fine riga, ecc.)
 *   line: La riga estratta (per liberarla in caso di errore nell'allocazione del remainder)
 * Note:
 *   - Se c'è del testo dopo il carattere newline, questo viene duplicato in un nuovo buffer
 *     (data.remainder) e il puntatore raw_input_ptr viene aggiornato per puntare a questo
 *   - Se non c'è testo dopo il newline o se non c'è un newline, il puntatore viene impostato a NULL
 *   - Il buffer originale (data.raw_input) viene sempre liberato
 *   - In caso di errore nell'allocazione del remainder, viene liberata anche la riga estratta */
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

/*read_and_update - Legge dati da un file descriptor e aggiorna il buffer di input
 * Questa funzione legge un blocco di dati dal file descriptor specificato
 * e lo aggiunge al buffer di input esistente (se presente). Gestisce
 * l'allocazione della memoria e la concatenazione dei dati.
 * Parametri:
 *   fd: File descriptor da cui leggere i dati
 *   raw_input_data: Buffer di input esistente (può essere NULL)
 * Valore di ritorno:
 *   Un puntatore al buffer aggiornato contenente tutti i dati, o NULL se:
 *   - L'allocazione di memoria fallisce
 *   - La lettura dal file descriptor fallisce
 *   Se non ci sono nuovi dati da leggere (EOF), restituisce il buffer originale
 * Note:
 *   - La funzione utilizza una dimensione di buffer definita da BUFFER_SIZE
 *   - Il buffer originale viene liberato dopo che i suoi contenuti sono stati
 *     copiati nel nuovo buffer (tranne in caso di errore o EOF)
 *   - La funzione utilizza ft_strdup per creare un nuovo buffer se raw_input_data è NULL
 *   - La funzione utilizza ft_strjoin per concatenare i dati esistenti con i nuovi */
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

/* get_next_line_reader - Legge dati da un file descriptor fino a trovare un newline o EOF
 *
 * Questa funzione è parte dell'implementazione di get_next_line e si occupa di
 * leggere dati dal file descriptor specificato fino a quando non viene trovato
 * un carattere newline ('\n') o viene raggiunta la fine del file (EOF).
 * Parametri:
 *   fd: File descriptor da cui leggere i dati
 *   raw_input_data: Buffer di input esistente (può essere NULL)
 * Valore di ritorno:
 *   Un puntatore al buffer contenente tutti i dati letti fino al newline o EOF,
 *   o NULL se si verifica un errore durante la lettura
 * Note:
 *   - La funzione continua a leggere in un ciclo fino a quando non trova un newline
 *     o raggiunge la fine del file
 *   - Utilizza read_and_update per leggere blocchi di dati dal file descriptor
 *   - Gestisce casi di errore liberando la memoria allocata
 *   - Il controllo "read_done == raw_input_data" determina se è stata raggiunta la
 *     fine del file (nessun nuovo dato letto)*/
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
/*get_next_line - Legge una riga da un file descriptor
 *
 * Questa funzione legge una riga da un file descriptor specificato e la
 * restituisce come una stringa terminata da null. Ad ogni chiamata successiva
 * con lo stesso file descriptor, restituisce la riga successiva.
 * Parametri:
 *   fd: File descriptor da cui leggere
 * Valore di ritorno:
 *   Una stringa contenente la riga letta, o NULL se:
 *   - Il parametro fd è invalido (negativo)
 *   - BUFFER_SIZE è impostato a un valore non positivo
 *   - La fine del file è stata raggiunta e non ci sono più dati da leggere
 *   - Si è verificato un errore durante la lettura
 * Note:
 *   - Utilizza una variabile statica raw_input_data per mantenere i dati tra le chiamate
 *   - Chiama get_next_line_reader per leggere dati fino a un newline o EOF
 *   - Chiama extract_line per estrarre una singola riga dal buffer
 *   - La riga restituita deve essere liberata dal chiamante quando non è più necessaria
 *   - Gestisce correttamente la pulizia della memoria in caso di errore o EOF */
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