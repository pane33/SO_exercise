# Esercizi di Sistemi Operativi (SO) in C

Questo repository contiene una raccolta di esercizi pratici in linguaggio C che coprono concetti fondamentali dei Sistemi Operativi.

Il progetto è una raccolta di esercizi universitari.

## 📚 Struttura del Repository

Ogni cartella (`ex_les_XX`) rappresenta un modulo o un set di lezioni su un argomento specifico di SO.

### 1. `ex_les_01_02_03` (Processi e Fork)
* Raccolta di esercizi sull'utilizzo della `fork()`.
* Gestione della comunicazione tra processi imparentati (padre e figlio).

### 2. `ex_les_04` (Segnali)
* Raccolta di esercizi sull'utilizzo della `kill()` per inviare segnali.
* Implementazione di `signal_handler` personalizzati per la gestione dei segnali.

### 3. `ex_les_05` (Pipe - Esempio Base)
* Esempio base sull'utilizzo delle pipe per la comunicazione tra processi imparentati.

### 4. `ex_les_06` (Pipe - Esercizi)
* Raccolta di esercizi sull'utilizzo delle pipe.
* Scenari di comunicazione sia tra processi imparentati che non imparentati.

### 5. `ex_les_07` (Code di Messaggi - Message Queues)
* Raccolta di esempi sull'utilizzo della coda di messaggi (IPC di System V).
* Utilizzo della struttura `msqid_ds`.
* Implementazione delle funzioni `msgsend()`, `msgrcv()`, `msgctl()`, ecc.

## 🛠️ Come Compilare ed Eseguire

La maggior parte degli esercizi può essere compilata individualmente utilizzando `gcc` (o `make` WIP).

**Esempio di compilazione (per un singolo file):**

```bash
# Spostati nella cartella dell'esercizio
cd ex_les_01_02_03

# Compila il file C
gcc nome_file.c -o nome_eseguibile

# Esegui il programma
./nome_eseguibile
```
## 🔧 Prerequisiti

* Un sistema operativo basato su UNIX (Linux, macOS).
* Un compilatore C (es. `gcc`).
* (Opzionale) `make` per l'esecuzione dei Makefile.

## 👤 Autore

* **pane33** - ([@pane33](https://github.com/pane33))
