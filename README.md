
***Aggiornato il 11/06/2025***

# Get Next Line

[![GNL](https://github.com/vhacman/get_next_line/actions/workflows/main.yml/badge.svg)](https://github.com/vhacman/get_next_line/actions/workflows/main.yml)
![42 Roma Luiss](https://img.shields.io/badge/42-Roma_Luiss-green)
![Score](https://img.shields.io/badge/Score-125/100-brightgreen)
![Created](https://img.shields.io/badge/Created-Febbraio_2025-blue)
![Status](https://img.shields.io/badge/Status-Completato-violet)

---

## 📖 Descrizione

**Get Next Line** (`get_next_line`) è una funzione C sviluppata durante il percorso 42 per leggere da un file descriptor **riga per riga**, gestendo la memoria in modo efficiente e supportando **più file descriptor** nella versione bonus.

---

## 💡 Caratteristiche

* Legge da un file descriptor **una riga alla volta**
* Supporta file, input standard e pipe
* Usa una dimensione di buffer configurabile (`BUFFER_SIZE`)
* **Bonus**: Letture simultanee da più file descriptor (`OPEN_MAX`)

---

## 🛠️ Competenze Tecniche

* Gestione dinamica della memoria senza perdite (leak-free)
* Variabili statiche per mantenere lo stato tra le chiamate
* Gestione efficiente del buffer
* Gestione ricorsiva di stringhe
* Bonus: Gestione di più file descriptor in parallelo

---

## 📁 Struttura File

```
gnl/
├── file_test/
│   └── file1.txt
│   └── file2.txt
│   └── file3.txt
│   └── test.txt
├── includes/
│   └── get_next_line.h
├── includes_bonus/
│   └── get_next_line_bonus.h
├── src/
│   ├── get_next_line.c           ← contiene un main() commentato per il testing
│   └── get_next_line_utils.c
├── src_bonus/
│   ├── get_next_line_bonus.c     ← contiene un main() commentato per il testing
│   └── get_next_line_utils_bonus.c
├── README.md
└── README_EN.md
```

> In `get_next_line.c` e `get_next_line_bonus.c` è presente un **main di test commentato** che può essere attivato per effettuare prove locali.

---

## 🔄 Logica della Funzione

### Versione Standard

1. **Valida** i parametri in input (`fd` e `BUFFER_SIZE`)
2. **Legge blocchi** di dati dal `fd` in un buffer dinamico
3. **Memorizza i dati residui** tra le chiamate (con variabile statica)
4. **Estrae una riga completa**, salvando il resto per la prossima chiamata
5. **Restituisce** la riga come `char *` oppure `NULL` a fine file

### Versione Bonus

* Usa un **array di buffer statici**, uno per file descriptor
* Indicizza i buffer tramite il file descriptor (fino a `OPEN_MAX`)
* Garantisce **stati indipendenti** per ogni `fd`
* Ideale per gestire **più file o pipe** nello stesso programma

---

## 🧪 Testing

### ✅ Test Standard

* File piccoli e grandi
* Nessun newline alla fine
* File vuoti
* File con una o più righe
* Input da pipe o `stdin`

### ✅ Test Bonus

* Lettura simultanea da più file
* Lettura alternata tra diversi `fd`
* File con righe di lunghezze diverse
* File descriptor aperti/chiusi in ordine casuale
* Conferma dell'indipendenza della memoria per `fd`

---

## ⚙️ Compilazione

### Mandatory

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    -Iincludes \
    src/get_next_line.c src/get_next_line_utils.c \
    -o gnl
```

### Bonus

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    -Iincludes_bonus \
    src_bonus/get_next_line_bonus.c src_bonus/get_next_line_utils_bonus.c \
    -o gnl_bonus
```

Puoi eseguire con:

```bash
./gnl          # Per testare la versione standard
./gnl_bonus    # Per testare la versione bonus
```

---


## 🤝 Contribuisci in modo rispettoso

Se trovi utile questo progetto, ti invito a non clonare direttamente la repository.

### ✨ Perché fare una fork?

Fare una **fork**:

* ti permette di avere una copia personale su cui lavorare liberamente;
* rende trasparente il tuo interesse per il progetto;
* mi aiuta a costruire un GitHub più professionale e tracciabile, mostrando quante persone hanno interagito realmente con il mio lavoro.

> 🚀 In questo modo posso far crescere il mio profilo e migliorare come sviluppatrice.

### ✅ Come procedere

1. Clicca in alto a destra su **Fork**
2. Clona la tua copia con:

```bash
git clone https://github.com/<il-tuo-username>/<nome-repo>.git
```

---
