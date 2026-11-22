# P4 — Approfondimento: come si implementa una coda

## Obiettivi e prerequisiti

Questa dispensa mostra **come realizzare** una coda FIFO, anziche' limitarsi a usare `std::queue`. Le prime implementazioni contengono **solo numeri interi** e **non usano template**: servono a capire array, indici, puntatori, allocazione dinamica e invarianti. Solo nella seconda parte viene introdotta la generalizzazione con `template<typename T>`.

Prerequisiti: classi, costruttori, metodi, array, puntatori, `new`/`delete`, riferimenti e `#pragma once`. Codice C++17.

## 1. L'ADT coda: una sola interfaccia, molte implementazioni

Una coda e' una struttura **FIFO** (*First In, First Out*): chi arriva per primo viene servito per primo. L'ADT definisce le operazioni, non la disposizione dei dati in memoria.

- `enqueue(x)`: inserisce in fondo (*rear*).
- `dequeue()`: elimina e restituisce l'elemento in testa (*front*).
- `front()`: consulta la testa senza eliminarla.
- `empty()`: verifica se e' vuota.
- `size()`: restituisce quanti elementi contiene.

**Convenzione usata qui:** `front` e `dequeue` restituiscono un `int`; se la coda e' vuota lanciano `std::underflow_error`. Nelle implementazioni con capacita' fissa, `enqueue` su coda piena lancia `std::overflow_error`. Non si confondono mai la coda vuota con un dato legittimo, per esempio `0` o `-1`.

Esempio comune:

```text
enqueue(10)  enqueue(20)  enqueue(30)
front -> [10][20][30] <- rear
dequeue() restituisce 10
front -> [20][30] <- rear
```

**Terminologia:** negli array `front` e `rear` saranno **indici interi**; nella lista concatenata saranno veri **puntatori a nodi**. Non sono la stessa cosa. Ogni esempio usa nomi di classi differenti per consentire di compilarli anche insieme.

---

## 2. Prima implementazione: array con shift a ogni estrazione

La testa e' sempre nella cella `dati[0]`. Dopo un'estrazione tutti gli elementi successivi vengono spostati di una posizione verso sinistra.

```text
Prima: [10][20][30][  ][  ]   n=3
dequeue()
Dopo: [20][30][  ][  ][  ]   n=2
```

### Codice completo

```cpp
#pragma once
#include <stdexcept>

class CodaShift {
private:
    static constexpr int CAPACITA = 5;
    int dati[CAPACITA];
    int n = 0;

public:
    bool empty() const { return n == 0; }
    bool full() const { return n == CAPACITA; }
    int size() const { return n; }

    void enqueue(int valore) {
        if (full()) throw std::overflow_error("Coda piena");
        dati[n] = valore;
        ++n;
    }

    int front() const {
        if (empty()) throw std::underflow_error("Coda vuota");
        return dati[0];
    }

    int dequeue() {
        if (empty()) throw std::underflow_error("Coda vuota");
        int valore = dati[0];
        for (int i = 1; i < n; ++i)
            dati[i - 1] = dati[i];
        --n;
        return valore;
    }
};
```

**Invariante:** gli elementi validi occupano sempre le celle `0 ... n-1`, in ordine FIFO. Le altre celle non devono essere lette.

**Costo:** inserimento O(1); estrazione O(n) a causa dello shift; lettura della testa O(1). E' molto semplice, ma inefficiente quando si estraggono molti elementi.

---

## 3. Seconda implementazione: array senza shift, con due indici

Invece di spostare i valori, si sposta l'indice della testa. `frontIndex` indica il primo elemento valido; `rearIndex` indica **la prossima cella libera**. Gli elementi validi occupano `[frontIndex, rearIndex)`.

```text
[10][20][30][  ][  ]    frontIndex=0 rearIndex=3
dequeue()
[--][20][30][  ][  ]    frontIndex=1 rearIndex=3
```

### Codice completo

```cpp
#pragma once
#include <stdexcept>

class CodaLineare {
private:
    static constexpr int CAPACITA = 5;
    int dati[CAPACITA];
    int frontIndex = 0;
    int rearIndex = 0;

public:
    bool empty() const { return frontIndex == rearIndex; }
    int size() const { return rearIndex - frontIndex; }

    void enqueue(int valore) {
        if (rearIndex == CAPACITA)
            throw std::overflow_error("Fine del vettore raggiunta");
        dati[rearIndex] = valore;
        ++rearIndex;
    }

    int front() const {
        if (empty()) throw std::underflow_error("Coda vuota");
        return dati[frontIndex];
    }

    int dequeue() {
        if (empty()) throw std::underflow_error("Coda vuota");
        int valore = dati[frontIndex];
        ++frontIndex;
        if (empty()) {
            // Quando non rimangono elementi, recuperiamo tutto lo spazio.
            frontIndex = 0;
            rearIndex = 0;
        }
        return valore;
    }
};
```

**Vantaggio:** inserimento ed estrazione O(1), senza spostamenti.

**Limite importante:** si puo' raggiungere la fine del vettore anche se sono rimaste celle inutilizzate all'inizio. Per esempio, dopo tre inserimenti e due estrazioni, lo spazio iniziale non e' recuperabile finche' la coda non diventa completamente vuota. Non si tratta necessariamente di una coda piena dal punto di vista logico: e' un **limite dell'implementazione lineare**. La soluzione e' riutilizzare circolarmente gli indici.

---

## 4. Terza implementazione: array circolare con front e rear

L'array viene interpretato come un anello. Dopo l'ultima cella si torna alla prima usando il modulo:

```cpp
indiceSuccessivo = (indiceCorrente + 1) % CAPACITA;
```

Adottiamo questa convenzione precisa:

- `frontIndex`: indice del **primo elemento valido**;
- `rearIndex`: indice della **prima posizione libera**, dove inserire;
- `n`: numero di elementi presenti.

Con il contatore `n` distinguiamo facilmente coda vuota (`n == 0`) e piena (`n == CAPACITA`), anche quando `frontIndex == rearIndex`. Un'alternativa e' rinunciare a una cella e considerare piena la coda quando `(rearIndex + 1) % CAPACITA == frontIndex`: e' una convenzione diversa, che offre solo `CAPACITA - 1` posti utili.

### Codice completo

```cpp
#pragma once
#include <stdexcept>

class CodaCircolare {
private:
    static constexpr int CAPACITA = 5;
    int dati[CAPACITA];
    int frontIndex = 0;
    int rearIndex = 0;
    int n = 0;

public:
    bool empty() const { return n == 0; }
    bool full() const { return n == CAPACITA; }
    int size() const { return n; }

    void enqueue(int valore) {
        if (full()) throw std::overflow_error("Coda piena");
        dati[rearIndex] = valore;
        rearIndex = (rearIndex + 1) % CAPACITA;
        ++n;
    }

    int front() const {
        if (empty()) throw std::underflow_error("Coda vuota");
        return dati[frontIndex];
    }

    int dequeue() {
        if (empty()) throw std::underflow_error("Coda vuota");
        int valore = dati[frontIndex];
        frontIndex = (frontIndex + 1) % CAPACITA;
        --n;
        return valore;
    }
};
```

### Simulazione con cinque celle

```text
enqueue(10), enqueue(20), enqueue(30):
indici       0    1    2    3    4
            [10] [20] [30] [ ]  [ ]
frontIndex=0, rearIndex=3, n=3

dequeue(), dequeue():
            [--] [--] [30] [ ]  [ ]
frontIndex=2, rearIndex=3, n=1

enqueue(40), enqueue(50), enqueue(60):
            [60] [--] [30] [40] [50]
frontIndex=2, rearIndex=1, n=4
Ordine logico: 30, 40, 50, 60
```

Le celle marcate `--` possono contenere ancora vecchi valori in memoria, ma **non fanno parte della coda**. Per percorrere i valori validi si parte da `frontIndex` e si eseguono `n` passi con il modulo.

**Costo:** `enqueue`, `dequeue`, `front`, `empty`, `size` sono O(1). La capacita' rimane fissa.

### Variante: rear indica l'ultimo elemento

In altri libri `rear` non indica la prossima cella libera, ma l'**ultima cella occupata**. Allora si incrementa `rear` **prima** dell'inserimento. Le due scelte sono entrambe corrette, ma non bisogna mescolarle: ogni implementazione deve dichiarare con precisione i propri invarianti.

---

## 5. Quarta implementazione: lista concatenata con puntatori front e rear

Un array ha una capacita' prestabilita. Una lista concatenata permette di creare un nodo quando arriva un elemento e distruggerlo quando esce. Ogni nodo contiene un `int` e un puntatore al nodo successivo.

```text
front                                 rear
  |                                     |
  v                                     v
[10 | *] --> [20 | *] --> [30 | nullptr]
```

In questa implementazione `frontPtr` e `rearPtr` sono **puntatori**, non indici. Per una coda vuota entrambi valgono `nullptr`.

### Codice completo

```cpp
#pragma once
#include <stdexcept>

class CodaLista {
private:
    struct Nodo {
        int valore;
        Nodo* prossimo;
        Nodo(int v) : valore(v), prossimo(nullptr) {}
    };

    Nodo* frontPtr = nullptr;
    Nodo* rearPtr = nullptr;
    int n = 0;

public:
    CodaLista() = default;

    // Evitiamo copie superficiali dei puntatori proprietari.
    CodaLista(const CodaLista&) = delete;
    CodaLista& operator=(const CodaLista&) = delete;

    ~CodaLista() {
        while (!empty()) dequeue();
    }

    bool empty() const { return frontPtr == nullptr; }
    int size() const { return n; }

    void enqueue(int valore) {
        Nodo* nuovo = new Nodo(valore);
        if (empty()) {
            frontPtr = nuovo;
            rearPtr = nuovo;
        } else {
            rearPtr->prossimo = nuovo;
            rearPtr = nuovo;
        }
        ++n;
    }

    int front() const {
        if (empty()) throw std::underflow_error("Coda vuota");
        return frontPtr->valore;
    }

    int dequeue() {
        if (empty()) throw std::underflow_error("Coda vuota");
        Nodo* vecchio = frontPtr;
        int valore = vecchio->valore;
        frontPtr = vecchio->prossimo;
        delete vecchio;
        --n;
        if (frontPtr == nullptr)
            rearPtr = nullptr;
        return valore;
    }
};
```

### Perche' servono entrambi i puntatori?

Con il solo `frontPtr`, per inserire in fondo bisognerebbe attraversare la lista, impiegando O(n). Conservando anche `rearPtr`, l'inserimento e' O(1).

Il caso piu' delicato e' l'estrazione dell'**ultimo** nodo: dopo `delete`, `frontPtr` e `rearPtr` devono tornare entrambi a `nullptr`. Lasciare `rearPtr` puntare alla memoria liberata produrrebbe un *dangling pointer*.

Il distruttore libera tutti i nodi ancora presenti. Poiche' la classe possiede memoria dinamica, le copie predefinite sarebbero pericolose: copierebbero solo gli indirizzi. Per questo l'esempio **vieta esplicitamente copia e assegnazione**. Una versione piu' avanzata puo' implementare copia profonda, spostamento e relativa gestione delle eccezioni (regola dei cinque).

**Costo:** `enqueue` e `dequeue` O(1); memoria O(n), piu' un puntatore per nodo. La disponibilita' di memoria non e' illimitata: `new` puo' fallire.

---

## 6. Confronto delle quattro implementazioni

| Implementazione | `enqueue` | `dequeue` | Memoria | Limite principale |
|---|---:|---:|---|---|
| Array con shift | O(1) | O(n) | O(C) | Spostamenti a ogni estrazione |
| Array lineare senza shift | O(1) | O(1) | O(C) | Celle iniziali non riutilizzabili finche' non si svuota |
| Array circolare | O(1) | O(1) | O(C) | Capacita' fissa C |
| Lista con front/rear | O(1) | O(1) | O(n) | Allocazione e deallocazione dinamica |

Qui C e' la capacita' dell'array, n il numero di elementi presenti. Le complessita' assumono operazioni elementari su `int`; non includono eventuali costi dell'allocatore.

**Quale scegliere?** Per comprendere gli indici, partire dallo shift; per mostrare perche' lo shift non serve, passare alla versione lineare; per una coda efficiente a capacita' fissa, usare il buffer circolare; per una coda con dimensione variabile, usare la lista concatenata. Nelle applicazioni ordinarie, preferire un contenitore standard.

---

# Parte II — Generalizzazione con i template

## 7. Perche' introdurre i template?

Le code precedenti funzionano soltanto con `int`. Se volessimo accodare `double`, `std::string` o `RichiestaScambio`, dovremmo riscrivere quasi lo stesso codice.

Un template permette di descrivere una volta sola l'algoritmo:

```cpp
template<typename T>
class Coda {
    // ...
};
```

`T` rappresenta il tipo degli elementi. Il compilatore genera le specializzazioni necessarie quando si usano, per esempio, `Coda<int>` e `Coda<std::string>`.

## 8. Esempio completo: coda circolare generica

La classe seguente usa `std::array<T, CAPACITA>` per mantenere il codice semplice e sicuro, senza gestire manualmente l'allocazione dell'array. Per questa specifica implementazione, `T` deve poter essere costruito senza argomenti e assegnato; e' una limitazione dell'uso di `std::array<T, CAPACITA>`, non dei template in generale.

```cpp
#pragma once
#include <array>
#include <cstddef>
#include <stdexcept>

template<typename T, std::size_t CAPACITA>
class CodaCircolareT {
    static_assert(CAPACITA > 0, "La capacita' deve essere positiva");

private:
    std::array<T, CAPACITA> dati;
    std::size_t frontIndex = 0;
    std::size_t rearIndex = 0;
    std::size_t n = 0;

public:
    bool empty() const { return n == 0; }
    bool full() const { return n == CAPACITA; }
    std::size_t size() const { return n; }

    void enqueue(const T& valore) {
        if (full()) throw std::overflow_error("Coda piena");
        dati[rearIndex] = valore;
        rearIndex = (rearIndex + 1) % CAPACITA;
        ++n;
    }

    const T& front() const {
        if (empty()) throw std::underflow_error("Coda vuota");
        return dati[frontIndex];
    }

    T dequeue() {
        if (empty()) throw std::underflow_error("Coda vuota");
        T valore = dati[frontIndex];
        frontIndex = (frontIndex + 1) % CAPACITA;
        --n;
        return valore;
    }
};
```

### Esempi di utilizzo

```cpp
#include <string>

CodaCircolareT<int, 5> numeri;
numeri.enqueue(10);
numeri.enqueue(20);
int x = numeri.dequeue();          // 10

CodaCircolareT<std::string, 3> nomi;
nomi.enqueue("Anna");
nomi.enqueue("Luca");
std::string primo = nomi.dequeue(); // "Anna"
```

**Nota:** il metodo `front()` restituisce un **riferimento costante** a un elemento interno. Il riferimento non va conservato dopo un'estrazione che ne elimina l'elemento. Il metodo `dequeue()` restituisce invece una copia (o un valore ottenuto mediante il costruttore di copia). Per tipi che possono lanciare eccezioni durante la copia o l'assegnazione, una implementazione generica di produzione richiede ulteriori garanzie di sicurezza; questa versione e' volutamente didattica.

## 9. Esempio completo: lista concatenata generica

```cpp
#pragma once
#include <cstddef>
#include <stdexcept>

template<typename T>
class CodaListaT {
private:
    struct Nodo {
        T valore;
        Nodo* prossimo;
        explicit Nodo(const T& v) : valore(v), prossimo(nullptr) {}
    };

    Nodo* frontPtr = nullptr;
    Nodo* rearPtr = nullptr;
    std::size_t n = 0;

public:
    CodaListaT() = default;
    CodaListaT(const CodaListaT&) = delete;
    CodaListaT& operator=(const CodaListaT&) = delete;

    ~CodaListaT() {
        while (frontPtr != nullptr) {
            Nodo* vecchio = frontPtr;
            frontPtr = frontPtr->prossimo;
            delete vecchio;
        }
    }

    bool empty() const { return frontPtr == nullptr; }
    std::size_t size() const { return n; }

    void enqueue(const T& valore) {
        Nodo* nuovo = new Nodo(valore);
        if (empty()) frontPtr = rearPtr = nuovo;
        else {
            rearPtr->prossimo = nuovo;
            rearPtr = nuovo;
        }
        ++n;
    }

    const T& front() const {
        if (empty()) throw std::underflow_error("Coda vuota");
        return frontPtr->valore;
    }

    // Due operazioni distinte, come in std::queue.
    void pop() {
        if (empty()) throw std::underflow_error("Coda vuota");
        Nodo* vecchio = frontPtr;
        frontPtr = frontPtr->prossimo;
        delete vecchio;
        --n;
        if (frontPtr == nullptr) rearPtr = nullptr;
    }
};
```

Esempio:

```cpp
CodaListaT<int> interi;
interi.enqueue(4);
interi.enqueue(7);
int primo = interi.front();
interi.pop();

CodaListaT<std::string> parole;
parole.enqueue("prima");
parole.enqueue("seconda");
```

La separazione `front()` / `pop()` evita di dover costruire un valore da restituire durante la rimozione. Anche qui la copia della coda e' vietata per evitare doppie deallocazioni. In C++, i template di classe e le definizioni dei loro metodi sono generalmente collocati nel file `.h`, affinche' il compilatore possa istanziarli nei file che li utilizzano.

## 10. Il collegamento con std::queue

`std::queue<T>` e' un **adattatore di contenitore**: fornisce l'interfaccia FIFO delegando la memorizzazione a un contenitore sottostante, normalmente `std::deque<T>`. Puo' essere usato anche con `std::list<T>`:

```cpp
#include <queue>
#include <list>

std::queue<int> numeri;                  // di norma usa std::deque<int>
std::queue<int, std::list<int>> altri;   // usa std::list<int>

numeri.push(10);
numeri.push(20);
int primo = numeri.front();
numeri.pop();                             // restituisce void
```

`std::queue` non garantisce che la propria implementazione interna corrisponda esattamente a uno dei nostri esempi: l'adattatore e il contenitore sottostante sono concetti distinti. `std::deque` e' una sequenza a doppia estremita', non necessariamente un unico array circolare.

Nel progetto P4:

```cpp
std::queue<RichiestaScambio> richieste;
```

Il tipo generico e' `RichiestaScambio`, non `int`. L'implementazione concreta della coda non deve cambiare la semantica del gestore: la richiesta piu' vecchia viene elaborata per prima.

## 11. Domande di verifica

1. Perche' l'estrazione nella coda con shift costa O(n)?
2. Perche' la coda lineare puo' non accettare inserimenti pur avendo celle inutilizzate?
3. Qual e' la differenza tra `rearIndex` come prossima cella libera e `rearIndex` come ultima cella occupata?
4. Come si distingue una coda circolare piena da una vuota quando gli indici coincidono?
5. Perche' una lista concatenata ha bisogno del puntatore `rearPtr`?
6. Che cosa accade se, eliminando l'ultimo nodo, non si azzera `rearPtr`?
7. Perche' copiare superficialmente una coda che possiede nodi dinamici e' pericoloso?
8. Quali vantaggi offre `template<typename T>` rispetto a una classe limitata a `int`?
9. Perche' `std::queue::pop()` non restituisce l'elemento?
10. Quale implementazione sceglieresti per un dispositivo con memoria fissa? Quale per una coda che deve crescere dinamicamente?

## 12. Proposta di laboratorio

Implementare e testare nell'ordine: `CodaShift`, `CodaLineare`, `CodaCircolare`, `CodaLista`. Usare per tutte la sequenza `enqueue(10), enqueue(20), enqueue(30), dequeue(), enqueue(40)` e verificare l'ordine delle estrazioni. Ripetere poi con una capacita' molto piccola per evidenziare le differenze fra array lineare e circolare. Infine convertire una delle implementazioni a template e provarla sia con `int` sia con `std::string`.

**Nota metodologica:** queste implementazioni sono esercizi di studio. Per la P4 applicativa rimane corretta la scelta di usare `std::queue<RichiestaScambio>`, senza sostituirla con una coda scritta manualmente.
