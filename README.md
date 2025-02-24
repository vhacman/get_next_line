# Get Next Line

## 📖 Panoramica
Get Next Line è una funzione che ho sviluppato in C come parte del curriculum di 42 Roma. Questa utility permette di leggere contenuti da un file descrittore riga per riga, gestendo in modo efficiente la memoria e supportando descrittori multipli.

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
- Supporto simultaneo per più descrittori di file
- Dimensione del buffer configurabile tramite la macro `BUFFER_SIZE`
- Gestione efficiente della memoria (senza memory leak)

## 🧩 Approccio Tecnico
Il progetto è strutturato in tre file principali:
- `get_next_line.h`: Contiene i prototipi delle funzioni e le definizioni delle strutture
- `get_next_line.c`: Implementa la funzione principale `get_next_line`
- `get_next_line_utils.c`: Contiene funzioni di utilità per la manipolazione delle stringhe

Ho implementato una soluzione che utilizza:
1. **Buffer dinamico** - Per leggere dati dal file in blocchi efficienti
2. **Variabile statica** - Per mantenere i dati rimanenti tra una chiamata e l'altra
3. **Struttura dati personalizzata** - Per gestire in modo organizzato i metadati delle linee

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

```bash
# Compilazione con dimensione buffer personalizzata
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# Esecuzione
./gnl
```
