# P4 — Le code FIFO e `std::queue`

## 1. Il problema
Una segreteria riceve richieste di scambio di lezioni: se arrivano R1, R2, R3, le elabora in questo ordine, una per volta. La richiesta non coincide con una modifica: puo' essere rifiutata.

## 2. ADT coda
La coda e' una struttura dati **FIFO** (*First In, First Out*). Il primo elemento inserito e' il primo estratto. La pila della P3 e' invece **LIFO** (*Last In, First Out*). La coda serve per il lavoro in attesa; la pila serve per annullare l'ultima modifica riuscita.

## 3. Operazioni C++17
```cpp
#include <queue>
std::queue<int> coda;
coda.push(10);             // inserisce in fondo
coda.push(20);
int primo = coda.front();  // legge 10 senza rimuoverlo
coda.pop();                // elimina 10
bool vuota = coda.empty();
std::size_t n = coda.size();
```
`front()` e `pop()` richiedono una coda non vuota. `pop()` non restituisce l'elemento eliminato. `std::queue` e' un **adattatore di contenitore**: espone le operazioni della coda, non l'accesso per indice o iteratori. Non e' corretto scrivere `coda[0]`.

## 4. La richiesta
`RichiestaScambio` conserva due `Posizione`, non puntatori alle tessere. Questo e' sufficiente per chiedere uno scambio in un momento successivo: le tessere presenti in quelle posizioni potrebbero nel frattempo essere cambiate.

## 5. Incapsulamento
`GestoreRichieste` contiene privatamente `std::queue<RichiestaScambio>`. L'interfaccia pubblica espone `Accoda`, `Vuota`, `NumeroRichieste`, `ElaboraPrima`. Non serve costruire una coda manuale con nodi.

## 6. Elaborazione
1. Se la coda e' vuota, restituire `EsitoRichiesta::CODA_VUOTA`.
2. Leggere `front()` e copiarne la richiesta.
3. Chiamare `MotoreScambi::Scambia` sull'orario corrente.
4. Eseguire `pop()` sia in caso di accettazione sia di rifiuto.
5. Restituire `ACCETTATA` oppure `RIFIUTATA`.

Il controllo dei vincoli avviene **solo al punto 3**. Se i vincoli sono stati modificati dopo l'accodamento, si usano quelli correnti. La richiesta rifiutata non modifica l'orario e non entra nella pila degli scambi riusciti.

## 7. Enumerazioni
`enum class EsitoRichiesta { CODA_VUOTA, ACCETTATA, RIFIUTATA };` distingue l'assenza di lavoro da un lavoro eseguito ma rifiutato. Il semplice `bool` non rappresenterebbe esplicitamente tutte e tre le condizioni.

## 8. Interazione con la pila P3
Uno scambio immediato o una richiesta accettata vengono registrati da `MotoreScambi`. `Annulla` riguarda l'ultimo scambio riuscito, non l'ultima richiesta inserita. Un annullamento rifiutato mantiene intatta la pila. L'annullamento controlla lo stato risultante con i vincoli correnti, anche quando lo stato iniziale non li rispetta.

## 9. Complessita'
Con il contenitore standard sottostante, `push`, `front`, `pop`, `empty` e `size` sono operazioni a costo costante per la normale coda `std::queue`. La verifica dei vincoli puo' richiedere invece un costo dipendente dalle dimensioni dell'orario.

## 10. Questioni per riflettere
- Perche' la pila non sarebbe adatta a garantire l'ordine di arrivo?
- Perche' una richiesta puo' diventare non valida prima di essere elaborata?
- Perche' `pop()` va eseguito anche quando lo scambio viene rifiutato?
- Che cosa accadrebbe se la UI modificasse direttamente l'orario senza usare il motore?
