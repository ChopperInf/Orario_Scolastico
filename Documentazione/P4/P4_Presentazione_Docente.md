# P4 — Presentazione del docente (scaletta)

## Slide 1 — Titolo
Le code FIFO e le richieste di scambio dell'orario. Dalla pila P3 alla coda P4.

## Slide 2 — Problema concreto
Richieste R1, R2, R3: come rispettare l'ordine di arrivo?

## Slide 3 — FIFO contro LIFO
Coda: prima entrata, prima uscita. Pila: ultima entrata, prima uscita. Due responsabilita' distinte.

## Slide 4 — `std::queue`
`push`, `front`, `pop`, `empty`, `size`; niente accesso indicizzato.

## Slide 5 — Richiesta non e' modifica
`RichiestaScambio` conserva due posizioni; `Modifica` rappresenta uno scambio riuscito.

## Slide 6 — Architettura
`InterfacciaConsole` → `GestoreRichieste` → `MotoreScambi` → `Orario`. La pila rimane nel motore.

## Slide 7 — Elaborazione
Controllo coda vuota → `front` → `Scambia` → `pop` → esito.

## Slide 8 — `enum class EsitoRichiesta`
`CODA_VUOTA`, `ACCETTATA`, `RIFIUTATA`: tre risultati distinti.

## Slide 9 — Vincoli correnti
Una richiesta valida all'inserimento puo' essere rifiutata piu' tardi. I vincoli si controllano all'elaborazione.

## Slide 10 — Pila e coda insieme
Scambio riuscito: pila aggiornata. Scambio rifiutato: solo rimozione dalla coda. Annullamento: ultima modifica riuscita.

## Slide 11 — Esercizio guidato
Accoda R1, R2; modifica il limite; elabora R1; annulla; elabora R2. Prevedere gli esiti.

## Slide 12 — Verifica finale
Spiegare perche' `pop()` non restituisce un valore e perche' la coda non ha `operator[]`. Verificare il comportamento su coda vuota.
