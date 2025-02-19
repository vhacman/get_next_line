/**TOD0
 * 1️⃣ Analizza il soggetto e scrivi un riassunto del problema.
 * 2️⃣ Scomponi il problema in piccoli passi e funzioni.
 * 3️⃣ Scrivi uno pseudo-codice per chiarire la logica.
 * 
 * 
 *                                             PROBOLEMI DA RISOLVERE:
 * - deve leggere una riga alla volta da un file descriptor(fd)
 * - ogni riga deve terminare con \n, a meno che sia l'ultima riga del file senza newline.
 * - deve gestire file di qualsiasi dimensione e funzionare bene anche con lo STDIN (0).
 * - Bisogna conservare i dati tra le chiamate successive per gestire correttamente le righe spezzate tra piu letture.
 * 
 *                                                SOTTOPROBLEMI:
 * - Leggere da file descriptor(fd) in blocchi BUFFER_SIZE
 * - accumulare i dati letti(una riga potrebbe essere spezzata su più read)
 * - estrarre una riga intera dall'accumulatore
 * - Restituire la riga e conservare il rwsto per la prossima chiamata
 * - gestire la fine del file e gli errori
 * 
 *                                             SCRIVI PSEUDOCODICE
 * - get_next_line
 * SE il fd non è valido
 *      RITORNA NULL
 * 
 *  
 * SE nel buffer statico è gia presente \n
        ESTRAI la riga completa
        RIMUOVI la riga estratta dal buffer statico
        RITORNA la riga trovata
 *
 *
 * 
   ***Se nel buffer statico è già presente un \n,
       significa che c'è già una riga completa.
       La estraiamo e la restituiamo subito.***
 * 
 * 
 *RIPETI finché non trova \n o EOF
        LEGGI fino a BUFFER_SIZE caratteri dal FD --> read(fd, buffer, BUFFER_SIZE)
        SE errore o fine del file
                SE buffer contiene dati, restituisci il contenuto
                ALTRIMENTI restituisci NULL
        CONCATENA i nuovi dati al buffer statico

        ESTRARRE la riga completa dal buffer
        RIMUOVERE la riga estratta dal buffer statico
        RITORNA la riga trovata
 * 
 *
 * 
 * 
 *                                          SCRIVI FUNZIONI DI SUPPORTO
 * - quella che trova \n nel buffer
 * - quella che unisce due stringhe
 * - quella che calcola la lunghezza della stringa
 * - quella che copia la stringa
 *                                        TESTA OGNI FUNZIONE PRIMA DI PROSEGUIRE
 * 
 *                      IMPLEMENTARE GET_NEXT_LINE
 * - prima gestisco solo la lettura del file (read() e accumulo)
 * - aggiungo la logica per estrarre la riga
 * - gestisco la memoria e gli edge cases
 */