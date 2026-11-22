# P4 — Piano dei test

Questi sono **casi da eseguire**, non risultati di test gia' svolti. Per gli scambi validi scegliere celle e limite ore che rispettino i vincoli del proprio orario di prova.

| ID | Preparazione / azione | Atteso |
|---|---|---|
| T01 | Elabora su coda vuota | `CODA_VUOTA`; orario e pila invariati |
| T02 | Accoda R1, R2, R3 | Numero richieste 3 |
| T03 | Elabora una volta | Solo R1 tentata; numero richieste 2 |
| T04 | Elabora due altre volte | R2 poi R3; numero richieste 0 |
| T05 | Accoda due posizioni identiche | Accodamento consentito; rifiuto all'elaborazione |
| T06 | Elabora richiesta rifiutata | `RIFIUTATA`; coda decrementata, pila invariata |
| T07 | Elabora richiesta valida | `ACCETTATA`; scambio e registrazione in pila |
| T08 | Annulla dopo T07 | Ripristino, se il risultato soddisfa i vincoli correnti |
| T09 | Cambia massimo ore dopo l'accodamento | Validazione con limite corrente |
| T10 | Esegui scambio immediato prima di elaborare | Richiesta valutata sull'orario aggiornato |
| T11 | Elabora R1, annulla, elabora R2 | FIFO indipendente da LIFO |
| T12 | Coda con richieste rifiutate e accettate | Tutte rimosse nell'ordine, solo accettate in pila |

## Criteri di accettazione
- Nessuna chiamata a `front()` o `pop()` su coda vuota.
- Nessuna modifica dell'orario durante `Accoda`.
- Nessuna duplicazione dei vincoli dentro `GestoreRichieste`.
- La P3 rimane compilabile e invariata.
- Compilazione ed esecuzione su Visual Studio 2022 devono essere verificate prima di dichiarare conclusa la P4.

## Scheda di prova
| ID | Input utilizzato | Risultato osservato | Superato (S/N) |
|---|---|---|---|
| T01 | | | |
| T02 | | | |
| T03 | | | |
| T04 | | | |
| T05 | | | |
| T06 | | | |
| T07 | | | |
| T08 | | | |
| T09 | | | |
| T10 | | | |
| T11 | | | |
| T12 | | | |
