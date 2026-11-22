# P3 — ADT pila, STL e annullamento

## 1. Il problema
Dopo uno scambio di due lezioni, vogliamo poter annullare l'ultima modifica. Se vengono eseguiti gli scambi A, B, C, l'ordine di annullamento e' C, B, A.

## 2. ADT pila
Una pila e' una struttura **LIFO** (Last In, First Out): l'ultimo elemento inserito e' il primo estratto. Le operazioni astratte sono inserimento in cima, consultazione della cima, estrazione dalla cima e controllo della pila vuota. Non si accede liberamente a un elemento intermedio.

| Operazione C++ | Significato | Precondizione |
|---|---|---|
| `push(x)` | Inserisce x in cima | Nessuna |
| `top()` | Restituisce un riferimento alla cima | Pila non vuota |
| `pop()` | Elimina la cima; non restituisce l'elemento | Pila non vuota |
| `empty()` | Controlla se la pila e' vuota | Nessuna |
| `size()` | Numero di elementi | Nessuna |

Esempio:
```cpp
#include <stack>
#include <iostream>
int main() {
    std::stack<int> pila;
    pila.push(10);
    pila.push(20);
    if (!pila.empty()) {
        std::cout << pila.top(); // 20
        pila.pop();              // ora in cima c'e' 10
    }
}
```
Le operazioni elencate hanno complessita' costante nel caso ordinario. `std::stack` e' un *adattatore di contenitore*: espone solo le operazioni tipiche della pila, appoggiandosi normalmente a un altro contenitore. Non e' necessario implementare manualmente nodi o puntatori.

## 3. Applicazioni
Cronologia di annullamento, navigazione a ritroso, bilanciamento di parentesi, valutazione di espressioni, visite con ritorno e gestione delle chiamate a funzione (analogia con lo stack delle chiamate, distinto da `std::stack`).

## 4. La classe Modifica
Nel progetto dell'orario lo scambio di due celle e' un'operazione reversibile: ripetere lo stesso scambio ripristina i puntatori originali. Per questo `Modifica` memorizza solo le due `Posizione`; non memorizza tessere, copie dell'orario o vincoli.

## 5. Contratto dello scambio
`MotoreScambi` possiede `std::stack<Modifica>`. `Scambia` controlla posizioni, validita' iniziale e finale; registra con `push` solo un successo. Un fallimento ripristina l'orario e non tocca la pila.

## 6. Contratto dell'annullamento
`Annulla` controlla `empty`, legge `top`, esegue temporaneamente lo scambio inverso e verifica **solo lo stato risultante** con i vincoli attuali. Se lo stato finale e' valido esegue `pop`; altrimenti ripristina le celle senza eseguire `pop`. Un annullamento rifiutato non modifica ne' orario ne' cronologia. L'utente puo' cambiare il limite di ore e riprovare. Non si salvano vecchi valori dei vincoli.

## 7. Invarianti e limiti
Ogni modifica ordinaria alle celle durante l'esecuzione deve passare da `MotoreScambi::Scambia`; il caricamento iniziale con `Set` avviene prima dell'uso del motore. Un motore e la sua cronologia si riferiscono a un solo orario. La pila non e' una copia dello stato: modifiche esterne alle celle renderebbero la cronologia inaffidabile.

## 8. Pila contro coda
La pila e' LIFO, la coda e' FIFO. In P4 una `std::queue` servira' a elaborare richieste nell'ordine di arrivo, mentre la `std::stack` continuera' a gestire gli annullamenti in ordine inverso.
