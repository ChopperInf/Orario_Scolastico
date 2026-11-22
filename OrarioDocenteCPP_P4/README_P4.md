# P4 — La coda FIFO e le richieste di scambio

La P4 estende il prototipo docente P3, senza modificarlo, introducendo `std::queue<RichiestaScambio>`. Soluzione Visual Studio 2022 (`OrarioDocenteCPP_P4.sln`), C++17, x64, MSVC v143.

## Novita'
- `Engine/RichiestaScambio.h`: due posizioni richieste, senza modificare l'orario.
- `Engine/GestoreRichieste.h/.cpp`: coda FIFO, `Accoda`, `Vuota`, `NumeroRichieste`, `ElaboraPrima`.
- `EsitoRichiesta`: `CODA_VUOTA`, `ACCETTATA`, `RIFIUTATA`.
- Menu 10: accoda; 11: elabora una richiesta; 12: numero richieste.
- Menu 3: scambio immediato; menu 9: annullamento LIFO, entrambi conservati.

## Regole
L'inserimento non verifica i vincoli. L'elaborazione tenta lo scambio usando `MotoreScambi::Scambia` e i vincoli correnti; rimuove sempre la richiesta dalla coda, anche quando rifiutata. Soltanto gli scambi riusciti vengono registrati nella pila P3. Coda vuota: nessuna modifica. Il programma non salva la coda su disco.

## Prove manuali
1. Elaborare a coda vuota: `CODA_VUOTA`, nessuna modifica.
2. Accodare R1 e R2, elaborare due volte: FIFO, numero richieste 2→1→0.
3. Accodare due posizioni uguali: inserimento consentito; rifiuto all'elaborazione e rimozione.
4. Accodare uno scambio valido, elaborare, annullare: l'orario torna allo stato precedente se i vincoli correnti lo permettono.
5. Modificare il massimo ore tra inserimento ed elaborazione: la validazione usa il limite aggiornato.

**Stato verifiche:** il codice e la soluzione sono predisposti; compilazione Visual Studio su Windows da verificare. La P3 rimane il riferimento già verificato.

[Materiali didattici P4](../Documentazione/P4/README.md).
