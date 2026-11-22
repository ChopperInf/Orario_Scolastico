# P3 — Eserciziario sull'ADT pila

Utilizzare `std::stack` della STL. Per ogni esercizio scrivere algoritmo, codice C++17, almeno tre test (normale, limite, errore) e motivare la scelta LIFO. Non usare una pila costruita manualmente.

## E1 — Simulazione della pila (base)
Data la sequenza `push(4), push(9), pop(), push(2), push(7), pop()`, disegnare la pila dopo ogni operazione, indicare `top()` finale e `size()`. Che cosa succede chiamando `top()` su una pila vuota?

## E2 — Inversione di una parola (base)
Leggere una parola e stamparla al contrario usando `std::stack<char>`. Esempio: `SCUOLA` → `ALOUCS`. Gestire anche la stringa vuota.

## E3 — Parentesi tonde bilanciate (base)
Scrivere `bool Bilanciate(string testo)` che ignori i caratteri diversi da `(` e `)`. Esempi: `(a+(b*c))` vero; `(()` falso; `())(` falso; stringa vuota vera.

## E4 — Tre tipi di parentesi (intermedio)
Estendere E3 a `() [] {}`, controllando **anche la corrispondenza del tipo**. Esempi: `{a+[b*(c+d)]}` vero, `([)]` falso, `{[}]` falso. Spiegare perche' il solo conteggio delle parentesi non basta.

## E5 — Cronologia di un editor (intermedio)
Simulare un editor che permette di aggiungere parole a una frase e annullare l'ultima aggiunta. Usare `std::stack<string>` per salvare lo stato precedente. Definire cosa accade se non ci sono modifiche da annullare.

## E6 — Conversione in binario (intermedio)
Dato un intero positivo, inserire in una pila i resti delle divisioni successive per 2, quindi estrarli per stampare la rappresentazione binaria. Provare 1, 13, 32 e 0 (caso speciale).

## E7 — Valutazione di un'espressione postfissa (avanzato)
Valutare una sequenza di interi separati da spazi con operatori `+ - *` usando `std::stack<int>`. Esempio: `3 4 + 2 *` → 14. Gestire operatori con meno di due operandi, input non valido e risultato con piu' di un elemento. Per sottrazione, rispettare l'ordine degli operandi.

## E8 — Cronologia dell'orario di classe (progetto)
Integrare `std::stack<Modifica>` nel motore P2 dello studente. Registrare solo scambi riusciti; annullare in ordine LIFO; rispettare i vincoli correnti; conservare stato e pila se l'annullamento fallisce. Preparare due scambi riusciti, un rifiuto e un annullamento inizialmente rifiutato e poi riuscito dopo modifica del vincolo.

## E9 — Ragionamento (avanzato)
Un utente esegue A, B, C; modifica un vincolo; l'annullamento di C fallisce. Puo' annullare B? Perche'? Come puo' rendere possibile un nuovo tentativo senza perdere la cronologia?

## E10 — Pila o coda? (confronto)
Per ciascun caso scegliere LIFO o FIFO e motivare: cronologia di annullamento, richieste di assistenza nell'ordine di arrivo, controllo parentesi, stampa di lavori nell'ordine di invio.


## E11 — Duplicare una pila (intermedio)
Scrivere una funzione `void Duplica(std::stack<int>& originale, std::stack<int>& copia)` che copi tutti gli elementi della pila `originale` nella pila `copia`, **mantenendo lo stesso ordine dalla cima al fondo**. Al termine, la pila originale deve essere invariata e la pila copia deve contenere soltanto gli elementi copiati (eventuali elementi precedenti vanno rimossi). Usare esclusivamente le operazioni dell'ADT pila e una pila ausiliaria; non utilizzare l'assegnamento diretto fra pile. Provare con una pila vuota, una con un elemento e una con piu' elementi.

## E12 — Eliminare l'elemento in posizione x (intermedio)
Scrivere `bool EliminaInPosizione(std::stack<int>& pila, int x)`. La posizione **0 indica la cima**, la posizione 1 l'elemento immediatamente sotto e cosi' via. Rimuovere l'elemento richiesto mantenendo invariato l'ordine degli altri. Restituire `false` e lasciare la pila invariata se `x < 0` o `x >= pila.size()`. Usare una pila ausiliaria, senza accedere direttamente agli elementi interni. Provare la rimozione della cima, di un elemento centrale, del fondo e una posizione non valida.

## E13 — Eliminare tutti i numeri pari (intermedio)
Scrivere `void EliminaPari(std::stack<int>& pila)` che elimini **tutti i valori pari**, compreso lo zero, preservando l'ordine relativo dei numeri dispari. Usare una pila ausiliaria e le sole operazioni dell'ADT. Provare con soli pari, soli dispari, numeri misti, numeri negativi e pila vuota. Spiegare perche' trasferire direttamente i dispari in una seconda pila, senza un ulteriore passaggio, ne invertirebbe l'ordine.

## Fonti e spunti didattici
La selezione riprende applicazioni classiche dell'ADT pila, adattate al livello di quarta Informatica. Per il contesto scolastico italiano: [programmazione di quarta Informatica dell'IIS Angioy](https://www.istitutoangioy.edu.it/wp-content/uploads/2025/06/4B_INFO_informatica.pdf) (ADT pila e laboratorio) e [programmazione dell'IIS Buccari-Marconi](https://www.buccarimarconi.edu.it/wp-content/uploads/ftp-explorer/programmazioni_disciplinari/2023-2024/Informatica-3Is.pdf) (strutture pila e coda). Gli esercizi qui formulati sono originali e non trascrizioni di materiali altrui.
