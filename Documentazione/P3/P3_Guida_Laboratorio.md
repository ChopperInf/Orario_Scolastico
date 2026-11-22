# P3 — Guida di laboratorio per gli studenti

## Obiettivo
Estendere il proprio progetto **OrarioClasse** della P2 con l'annullamento degli scambi riusciti, usando `std::stack`. Il progetto docente `OrarioDocenteCPP_P3` e' un riferimento di metodo, non codice da copiare: l'orario di classe mantiene le sue tessere e i suoi vincoli (continuita' della giornata e massimo ore della stessa materia).

## Preparazione
1. Conservare P2 e creare una copia autonoma per P3.
2. Aprire la soluzione in Visual Studio; verificare che P2 compili.
3. Individuare il metodo di scambio, il punto in cui viene confermato e la verifica dei vincoli.
4. Scrivere su carta la sequenza di tre scambi e dei rispettivi annullamenti.

## Attivita' A — Modella la cronologia
Creare `Modifica` con due posizioni e aggiungere `std::stack<Modifica>` nella classe che gestisce lo scambio. Spiegare perche' non occorre salvare le tessere.

## Attivita' B — Registra gli scambi
Modificare il metodo di scambio affinche' registri soltanto quelli riusciti. Provare uno scambio rifiutato e dimostrare che la cronologia non cambia.

## Attivita' C — Annulla
Aggiungere un metodo pubblico `Annulla`. Verificare la pila vuota; consultare la cima senza rimuoverla; tentare lo scambio inverso; controllare lo stato finale con i vincoli correnti; eliminare la cima solo in caso di successo.

**Requisito obbligatorio:** se l'annullamento fallisce, orario e pila restano identici a prima. Anche partendo da un orario non valido, l'annullamento e' ammesso se il risultato e' valido.

## Attivita' D — Menu e messaggi
Aggiungere una voce di menu. In caso di rifiuto indicare il vincolo non rispettato e suggerire di cambiare i parametri prima di riprovare.

## Attivita' E — Test
| Prova | Risultato |
|---|---|
| Pila vuota | Messaggio, nessuna modifica |
| Due scambi validi e due annullamenti | Orario iniziale ripristinato |
| Scambio rifiutato | Nessuna registrazione |
| Annullamento rifiutato | Orario e pila invariati |
| Modifica limite e nuovo tentativo | Annullamento possibile quando il risultato e' valido |
| Stato iniziale non valido, finale valido | Annullamento consentito |

## Consegna
Consegnare soluzione Visual Studio funzionante, spiegazione di `push/top/pop/empty`, tabella dei test effettivamente svolti e una breve risposta: perche' una coda non sarebbe adatta a questa cronologia?

## Vincoli
Non implementare una pila con nodi, non usare `cout` nel motore, non duplicare la verifica dei vincoli, non modificare retroattivamente P2. Tutte le modifiche ordinarie alle celle passano dal motore.
