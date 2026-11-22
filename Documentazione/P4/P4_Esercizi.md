# P4 — Eserciziario sulle code FIFO

Per ogni esercizio utilizzare `std::queue` e indicare come si gestisce la coda vuota. Gli esercizi di programmazione possono essere svolti in un programma console autonomo, salvo indicazione diversa.

## Esercizio 1 — FIFO sulla carta
Una coda riceve A, B, C. Si esegue `pop`, poi `push(D)`, poi `pop`. Indicare l'ordine delle estrazioni e il contenuto finale.

## Esercizio 2 — Operazioni fondamentali
Scrivere un programma che inserisca cinque interi in una `std::queue<int>`, mostri il primo elemento, il numero degli elementi e poi svuoti la coda visualizzando ogni valore.

## Esercizio 3 — Sportello
Simulare l'arrivo di cinque clienti (numeri progressivi) e la chiamata di un cliente per volta. Gestire la coda vuota.

## Esercizio 4 — Duplicare una coda
Realizzare una funzione che riceva una coda di interi **per valore** e restituisca una nuova coda con gli stessi elementi e lo stesso ordine. Spiegare perche' la coda originale non cambia.

## Esercizio 5 — Eliminare un elemento in posizione x
Data una coda e una posizione `x` (prima posizione = 0), restituire una nuova coda priva dell'elemento in posizione `x`, mantenendo l'ordine degli altri. Se `x` non esiste, lasciare tutti gli elementi.

## Esercizio 6 — Eliminare i numeri pari
Data una coda di interi, produrre una nuova coda contenente soltanto i numeri dispari, nello stesso ordine.

## Esercizio 7 — Somma degli elementi
Calcolare la somma degli elementi senza alterare la coda originale. Spiegare il costo dell'algoritmo.

## Esercizio 8 — Invertire una coda
Utilizzare una `std::stack` ausiliaria per ottenere una nuova coda con l'ordine inverso. Descrivere il ruolo di FIFO e LIFO.

## Esercizio 9 — Due code di priorita' didattiche
Simulare due code distinte, una per richieste ordinarie e una per urgenti. Elaborare prima le urgenti, preservando FIFO **all'interno** di ogni coda. Spiegare perche' non e' piu' una FIFO globale.

## Esercizio 10 — Richiesta o modifica?
Indicare quali oggetti devono essere inseriti nella coda e quali nella pila per i casi: richiesta appena ricevuta, scambio rifiutato, scambio riuscito, annullamento riuscito.

## Esercizio 11 — Progettazione del gestore
Descrivere gli attributi e i metodi pubblici di `GestoreRichieste`. Motivare perche' il contenitore e' privato e perche' non si devono duplicare i vincoli.

## Esercizio 12 — Validazione differita
Accodare R1 e R2, cambiare il limite massimo di ore, poi elaborare R1. Quale limite va applicato? Cosa succede a R1 se rifiutata?

## Esercizio 13 — Test di integrazione
Progettare una sequenza di richieste, scambi immediati e annullamenti che dimostri l'indipendenza fra coda FIFO e pila LIFO. Specificare gli esiti attesi.

## Esercizio 14 — Analisi di un errore
Un programmatore chiama `front()` su coda vuota e suppone che `pop()` restituisca l'elemento eliminato. Individuare e correggere entrambi gli errori.
