# Get Next Line (GNL)

![42 Roma Luiss](https://img.shields.io/badge/42-Roma_Luiss-green)
![125](https://img.shields.io/badge/125-green)
![Created](https://img.shields.io/badge/Created-February_2025-blue)
![Status](https://img.shields.io/badge/Status-Completed-violet)

## 📖 Panoramica
Get Next Line è una funzione sviluppata in C come parte del curriculum di 42 Roma. Questa utility permette di leggere contenuti da un file descrittore riga per riga, gestendo in modo efficiente la memoria e supportando descrittori multipli.

![C](https://img.shields.io/badge/Linguaggio-C-blue)
![42](https://img.shields.io/badge/Progetto-42_Roma-white)

## 🛠️ Competenze Tecniche Dimostrate
- **Gestione avanzata della memoria in C** - Allocazioni dinamiche senza memory leak
- **Utilizzo efficiente di puntatori e strutture dati**
- **Gestione di file e descrittori multipli**
- **Trattamento di variabili statiche per preservare lo stato tra chiamate**
- **Sviluppo di algoritmi efficienti per l'I/O**

## 💡 Caratteristiche Principali
- Lettura di testo da un descrittore di file una riga alla volta
- Gestione appropriata dei caratteri di newline
- Dimensione del buffer configurabile tramite la macro `BUFFER_SIZE`
- Gestione efficiente della memoria (senza memory leak)

### ⭐ Caratteristiche della Versione Bonus
- Supporto simultaneo per più descrittori di file
- Gestione efficiente di file multipli senza interferenze tra i buffer
- Utilizzo di un array statico di buffer dimensionato con `OPEN_MAX`
- Perfetta compatibilità con la versione standard

## 🧩 Approccio Tecnico
Il progetto è strutturato in tre file principali per la versione standard:
- `get_next_line.h`: Contiene i prototipi delle funzioni e le definizioni delle strutture
- `get_next_line.c`: Implementa la funzione principale `get_next_line`
- `get_next_line_utils.c`: Contiene funzioni di utilità per la manipolazione delle stringhe

### Versione Bonus
La versione bonus aggiunge:
- `get_next_line_bonus.h`: Header file con supporto per file descrittori multipli
- `get_next_line_bonus.c`: Implementazione della funzione con supporto multi-FD
- `get_next_line_utils_bonus.c`: Funzioni di utilità ottimizzate per la versione bonus

Ho implementato una soluzione che utilizza:
1. **Buffer dinamico** - Per leggere dati dal file in blocchi efficienti
2. **Variabile statica** - Per mantenere i dati rimanenti tra una chiamata e l'altra
3. **Struttura dati personalizzata** - Per gestire in modo organizzato i metadati delle linee
4. **Array statico di buffer** - Nella versione bonus, per gestire più file descrittori

## 🔄 Funzionamento
La funzione `get_next_line` opera secondo il seguente flusso:
1. Verifica la validità del file descriptor e della dimensione del buffer
2. Legge dal file descriptor e accumula i dati nel buffer fino a trovare un carattere newline o EOF
3. Estrae la prima riga completa dal buffer
4. Conserva i dati rimanenti per la prossima chiamata
5. Restituisce la riga estratta come stringa terminata da null

### Funzionamento della Versione Bonus
La versione bonus estende il funzionamento standard:
1. Utilizza un array statico di buffer dimensionato con `OPEN_MAX` per gestire contemporaneamente più file descriptor
2. Associa ogni buffer a un FD specifico tramite l'indice dell'array
3. Mantiene lo stato separato per ogni file descriptor, permettendo letture alternate da più file
4. Verifica che l'FD sia valido (non negativo e inferiore a `OPEN_MAX`)
5. Gestisce in modo indipendente la memoria per ogni file descriptor

L'implementazione bonus garantisce che la lettura da un file non interferisca con lo stato degli altri file aperti.

## 📋 Esempio di Utilizzo
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    
    fd = open("testo.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Errore nell'apertura del file\n");
        return (1);
    }
    
    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    
    close(fd);
    return (0);
}
```

## 🔍 Sfide e Soluzioni
- **Sfida**: Gestire correttamente il buffer tra chiamate successive
  - **Soluzione**: Utilizzo di una variabile statica che conserva i dati non ancora elaborati
- **Sfida**: Evitare memory leak durante la gestione di stringhe
  - **Soluzione**: Attenta gestione della memoria con free() appropriati in tutti i percorsi di codice
- **Sfida**: Supportare più file descrittori contemporaneamente
  - **Soluzione**: Implementazione di un array statico per tenere traccia dei buffer per ogni descrittore

## 🎓 Cosa ho imparato
- Approfondito la comprensione dei puntatori e dell'allocazione dinamica della memoria
- Migliorato le tecniche di debugging e testing per programmi con gestione complessa dello stato
- Affinato la capacità di scrivere codice pulito, modulare e ben documentato
- Migliorato la comprensione delle operazioni di I/O in C

## 💻 Compilazione e Test

### Versione Standard
```bash
# Compilazione con dimensione buffer personalizzata
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# Esecuzione
./gnl
```

### Versione Bonus
```bash
# Compilazione della versione bonus
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus

# Esecuzione
./gnl_bonus
```

### Esempio di main per testare la versione bonus
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1;
    int     fd2;
    int     fd3;
    char    *line;
    
    // Apertura di diversi file
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);
    
    if (fd1 == -1 || fd2 == -1 || fd3 == -1)
    {
        printf("Errore nell'apertura dei file\n");
        return (1);
    }
    
    // Legge alternativamente dai tre file
    line = get_next_line(fd1);
    printf("File 1: %s", line);
    free(line);
    
    line = get_next_line(fd2);
    printf("File 2: %s", line);
    free(line);
    
    line = get_next_line(fd3);
    printf("File 3: %s", line);
    free(line);
    
    // Continua a leggere dal primo file
    line = get_next_line(fd1);
    printf("File 1: %s", line);
    free(line);
    
    // Chiusura dei file
    close(fd1);
    close(fd2);
    close(fd3);
    
    return (0);
}
```

## 📚 Documentazione del Codice
Ogni funzione nel codice è documentata con commenti dettagliati che spiegano:
- Lo scopo della funzione
- I parametri di input e il loro significato
- I valori di ritorno e il loro significato
- Casi particolari e gestione degli errori

## 🧪 Testing

### Testing Generale
Il progetto è stato rigorosamente testato con:
- File di varie dimensioni (da pochi byte a diversi megabyte)
- File con e senza caratteri newline
- File vuoti
- Casi limite con BUFFER_SIZE impostato a valori molto piccoli e molto grandi

### Testing Specifico della Versione Bonus
Per la versione bonus, sono stati eseguiti test aggiuntivi:
- Uso simultaneo di più file descriptor (fino al limite OPEN_MAX)
- Lettura alternata da file diversi per verificare l'indipendenza dei buffer
- Apertura e chiusura di file descrittori in sequenze complesse
- Test con file descriptor non sequenziali
- Verifica di gestione corretta della memoria anche con operazioni interleaved su file diversi

## 📝 Note Aggiuntive
Questo progetto è stato sviluppato seguendo rigorosamente le linee guida e i requisiti di 42 Roma, incluso il rispetto della Norma di codifica.

## 🔍 Differenze tra Versione Standard e Bonus

| Caratteristica | Versione Standard | Versione Bonus |
|----------------|-------------------|----------------|
| Supporto Multi-FD | ❌ | ✅ |
| Struttura dati per buffer | Singola variabile statica | Array statico `fd_buffers[OPEN_MAX]` |
| Complessità implementativa | Media | Alta |
| Gestione della memoria | Per singolo FD | Per ogni FD nell'array |
| Verifica limiti FD | Solo validità generale | Controllo `fd < 0 || fd >= OPEN_MAX` |
| File sorgente | get_next_line.c | get_next_line_bonus.c |
| Header | get_next_line.h | get_next_line_bonus.h |

La versione bonus rappresenta un'estensione significativa della funzionalità standard, mantenendo al contempo la compatibilità con l'interfaccia originale.
