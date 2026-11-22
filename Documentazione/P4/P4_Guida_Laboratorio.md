# P4 — Guida di laboratorio per gli studenti

## Obiettivo
Estendere il proprio progetto **OrarioClasse P3** con una coda FIFO di richieste di scambio, preservando il motore, i vincoli della classe e la pila degli annullamenti. Il progetto docente `OrarioDocenteCPP_P4` e' un riferimento architetturale, non codice da copiare.

## Preparazione
1. Creare una copia autonoma del progetto P3; non modificare P3.
2. Compilare la copia prima di introdurre nuove classi.
3. Individuare `MotoreScambi::Scambia` (o il metodo equivalente) e il punto che registra gli scambi riusciti.

## Attivita' A — Modello
Creare `RichiestaScambio` con due posizioni e metodi `GetPrima` e `GetSeconda`. Non conservare le tessere: tra accodamento ed elaborazione l'orario puo' cambiare.

## Attivita' B — Coda
Creare `GestoreRichieste` con una `std::queue<RichiestaScambio>` privata. Realizzare `Accoda`, `Vuota`, `NumeroRichieste`. Non verificare i vincoli in `Accoda`.

## Attivita' C — Esiti
Dichiarare `enum class EsitoRichiesta` con `CODA_VUOTA`, `ACCETTATA`, `RIFIUTATA`. Spiegare perche' non basta un `bool`.

## Attivita' D — Elaborazione
Realizzare `ElaboraPrima`: controllo `empty`, lettura `front`, chiamata al motore, `pop` in entrambi gli esiti, restituzione del valore enumerato. Non duplicare la verifica dei vincoli nel gestore.

## Attivita' E — Menu
Aggiungere: accoda richiesta, elabora prima richiesta, mostra numero in attesa. Conservare lo scambio immediato e l'annullamento. La UI gestisce `cout`; il motore e il gestore non stampano messaggi.

## Attivita' F — Test
Provare: coda vuota; FIFO su tre richieste; rifiuto con rimozione; modifica di un vincolo dopo l'inserimento; scambio riuscito seguito da annullamento; interazione fra scambi immediati e richieste.

## Consegna
Soluzione Visual Studio, file `.h/.cpp`, breve relazione sulle differenze fra pila e coda e tabella dei test realmente eseguiti (input, esito atteso, esito ottenuto).

## Vincoli didattici
Usare `std::queue` e `#pragma once`. Evitare implementazioni con nodi, ereditarieta' aggiuntiva e persistenza su file. La coda degli studenti deve gestire l'orario della **classe**, non replicare i vincoli dell'orario del docente.
