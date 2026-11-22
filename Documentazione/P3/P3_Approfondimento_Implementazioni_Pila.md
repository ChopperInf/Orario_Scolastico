# P3 — Approfondimento: come si può implementare una pila

**Destinatari:** classe quarta Informatica · **Prerequisiti:** array, puntatori, classi, costruttori e distruttori, memoria dinamica, introduzione a `std::stack`.

Questo approfondimento distingue **ADT pila** (le operazioni offerte) e **struttura dati** (come gli elementi sono memorizzati). Le implementazioni sono volutamente didattiche: nella **parte I** tutte le pile contengono soltanto `int`, senza template; nella **parte II** si introducono i template.

## 1. Il contratto dell'ADT pila

Una pila è **LIFO** (*Last In, First Out*). Consideriamo quattro operazioni:

- `Push(valore)`: inserisce in cima;
- `Pop(valore)`: rimuove la cima e la restituisce tramite parametro per riferimento;
- `Top(valore)`: legge la cima senza rimuoverla;
- `Empty()`: indica se la pila è vuota.

Nelle implementazioni a capacità fissa `Push` restituisce `false` se non c'è spazio; `Pop` e `Top` restituiscono `false` se la pila è vuota. **Non confondere** questo `Pop(int&)` didattico con `std::stack::pop()`, che non restituisce un elemento.

Convenzione dei disegni: `[10, 20, 30]` elenca gli elementi **dal fondo alla cima**; la cima è 30. Dopo `Push(40)`: `[10, 20, 30, 40]`; dopo `Pop`: `[10, 20, 30]`.

Per semplicità le prime implementazioni hanno capacità costante `CAP = 5`. Un **array statico** è una struttura a dimensione fissa; in questa dispensa usiamo il termine «vettore» nel significato scolastico di array, **non** necessariamente `std::vector`.

---

# Parte I — Pile di interi, senza template

## 2. Vettore senza shift: cima nell'ultima posizione occupata

La rappresentazione più semplice usa `int dati[CAP]` e un **indice intero** `top`. In una pila vuota `top = -1`. Gli elementi occupano sempre `dati[0] ... dati[top]`.

```text
indice:  0    1    2    3    4
dati:   [10] [20] [30] [  ] [  ]
                  ^
                top = 2
```

```cpp
#pragma once

class PilaInteriFine {
private:
    static const int CAP = 5;
    int dati[CAP];
    int top; // Indice dell'ultimo elemento; -1 se vuota.

public:
    PilaInteriFine() : top(-1) {}

    bool Empty() const { return top == -1; }

    bool Push(int valore) {
        if (top == CAP - 1) return false;
        top++;
        dati[top] = valore;
        return true;
    }

    bool Top(int& valore) const {
        if (Empty()) return false;
        valore = dati[top];
        return true;
    }

    bool Pop(int& valore) {
        if (Empty()) return false;
        valore = dati[top];
        top--;
        return true;
    }
};
```

**Invariante:** `-1 <= top < CAP`. Nessuno spostamento degli elementi: `Push`, `Pop`, `Top` sono **O(1)**. Il valore rimasto fisicamente in una cella dopo `Pop` non fa più parte della pila: è `top` a determinare quali celle sono valide.

## 3. Vettore senza shift: cima nella prima posizione occupata

Si può collocare la cima **verso l'inizio** dell'array evitando comunque lo shift, ma gli elementi devono occupare la parte destra: `dati[top] ... dati[CAP-1]`. Quando la pila è vuota, `top = CAP`.

```text
indice:  0    1    2    3    4
dati:   [  ] [  ] [30] [20] [10]
                  ^
                top = 2
```

```cpp
#pragma once

class PilaInteriInizioSenzaShift {
private:
    static const int CAP = 5;
    int dati[CAP];
    int top; // Prima posizione occupata; CAP se vuota.

public:
    PilaInteriInizioSenzaShift() : top(CAP) {}

    bool Empty() const { return top == CAP; }

    bool Push(int valore) {
        if (top == 0) return false;
        top--;
        dati[top] = valore;
        return true;
    }

    bool Top(int& valore) const {
        if (Empty()) return false;
        valore = dati[top];
        return true;
    }

    bool Pop(int& valore) {
        if (Empty()) return false;
        valore = dati[top];
        top++;
        return true;
    }
};
```

Anche qui tutte le operazioni sono **O(1)**. La differenza è la **direzione di crescita**: la pila cresce verso indici decrescenti. **Cima all'indice basso non significa necessariamente shift**.

## 4. Vettore con shift: cima sempre in `dati[0]`

Se vogliamo che la cima sia **sempre esattamente in posizione 0**, e che il resto della pila sia contiguo da 0 in poi, ogni inserimento deve spostare gli elementi di una posizione verso destra; ogni estrazione li sposta a sinistra.

```text
Prima:       [30] [20] [10] [  ] [  ]    cima = dati[0]
Push(40):    [40] [30] [20] [10] [  ]
Pop():       [30] [20] [10] [  ] [  ]
```

```cpp
#pragma once

class PilaInteriInizioConShift {
private:
    static const int CAP = 5;
    int dati[CAP];
    int quanti; // Numero di elementi presenti.

public:
    PilaInteriInizioConShift() : quanti(0) {}

    bool Empty() const { return quanti == 0; }

    bool Push(int valore) {
        if (quanti == CAP) return false;
        for (int i = quanti; i > 0; i--)
            dati[i] = dati[i - 1];
        dati[0] = valore;
        quanti++;
        return true;
    }

    bool Top(int& valore) const {
        if (Empty()) return false;
        valore = dati[0];
        return true;
    }

    bool Pop(int& valore) {
        if (Empty()) return false;
        valore = dati[0];
        for (int i = 0; i < quanti - 1; i++)
            dati[i] = dati[i + 1];
        quanti--;
        return true;
    }
};
```

**Invariante:** `0 <= quanti <= CAP`, celle valide `[0, quanti)`, cima `dati[0]` se `quanti > 0`. `Push` e `Pop` richiedono **O(n)** spostamenti; `Top` è **O(1)**. I cicli hanno direzioni diverse per non sovrascrivere valori ancora necessari.

### 4.1 E se la cima fosse all'ultimo indice con shift?

È possibile, ma **non necessario**. Per esempio si potrebbe imporre che la cima sia sempre in `dati[CAP-1]`, mantenendo gli elementi a destra: ad ogni `Push` si spostano gli elementi a sinistra per liberare l'ultima cella; a ogni `Pop` si spostano a destra. Anche in questo caso `Push` e `Pop` sono **O(n)**. Il confronto utile è quindi tra **posizione fissa della cima** e **indice della cima che si sposta**, non semplicemente «primo» contro «ultimo».

## 5. Indice `top` oppure puntatore `top`?

Negli esempi precedenti `top` è un **intero**: indica una posizione dell'array. Un'altra possibilità è memorizzare un vero **puntatore a int** che indica la cella di cima. Questo non è ancora una lista collegata.

```cpp
class PilaInteriPuntatoreArray {
private:
    static const int CAP = 5;
    int dati[CAP];
    int* top; // Punta alla prossima cella libera.

public:
    PilaInteriPuntatoreArray() : top(dati) {}

    bool Empty() const { return top == dati; }

    bool Push(int valore) {
        if (top == dati + CAP) return false;
        *top = valore;
        top++;
        return true;
    }

    bool Top(int& valore) const {
        if (Empty()) return false;
        valore = *(top - 1);
        return true;
    }

    bool Pop(int& valore) {
        if (Empty()) return false;
        top--;
        valore = *top;
        return true;
    }
};
```

**Attenzione alla convenzione:** qui `top` punta alla **prima cella libera**, non all'ultimo elemento. La cima effettiva è `*(top - 1)`. La posizione `dati + CAP` è un puntatore valido *one-past-the-end*, ma **non può essere dereferenziato**. Questa rappresentazione richiede attenzione anche alle copie: il compilatore copierebbe il puntatore `top` senza ricollegarlo all'array della copia. Per un uso sicuro, bisognerebbe implementare correttamente copia e assegnamento oppure disabilitarli. In un primo laboratorio è preferibile l'indice intero.

## 6. Pila dinamica: nodi collegati con puntatore alla cima

Una pila può crescere senza capacità prefissata usando nodi allocati dinamicamente. Ogni nodo contiene un intero e un puntatore al nodo sottostante. Il puntatore `top` indica il **primo nodo della lista**, cioè la cima.

```text
top ──> [30 | *] ──> [20 | *] ──> [10 | nullptr]
```

```cpp
#pragma once

class PilaInteriNodi {
private:
    struct Nodo {
        int valore;
        Nodo* prossimo;
    };
    Nodo* top;

public:
    PilaInteriNodi() : top(nullptr) {}

    // Impedisce copie superficiali dei puntatori ai nodi.
    PilaInteriNodi(const PilaInteriNodi&) = delete;
    PilaInteriNodi& operator=(const PilaInteriNodi&) = delete;

    ~PilaInteriNodi() {
        int ignorato;
        while (Pop(ignorato)) {}
    }

    bool Empty() const { return top == nullptr; }

    bool Push(int valore) {
        Nodo* nuovo = new Nodo{valore, top};
        top = nuovo;
        return true;
    }

    bool Top(int& valore) const {
        if (Empty()) return false;
        valore = top->valore;
        return true;
    }

    bool Pop(int& valore) {
        if (Empty()) return false;
        Nodo* daEliminare = top;
        valore = daEliminare->valore;
        top = daEliminare->prossimo;
        delete daEliminare;
        return true;
    }
};
```

Il nodo nuovo diventa la cima e punta alla vecchia cima. Durante `Pop` bisogna **salvare il nodo da eliminare**, aggiornare `top` e infine eseguire `delete`. Le operazioni sono **O(1)**; lo spazio occupato è **O(n)**, con un puntatore aggiuntivo per nodo. `new` può fallire lanciando un'eccezione: il valore `true` di `Push` non significa che l'allocazione sia garantita.

### 6.1 E se il puntatore `top` fosse all'ultimo nodo?

In una **lista semplicemente collegata dal primo verso l'ultimo**, se `top` indicasse l'ultimo nodo, togliere la cima richiederebbe di trovare il **penultimo** nodo partendo dal primo: `Pop` sarebbe **O(n)**. Con una **lista doppiamente collegata** si potrebbe invece risalire al precedente in **O(1)**, pagando un secondo puntatore per nodo. Per una pila è naturale tenere la cima alla **testa della lista semplicemente collegata**: sia inserimento sia rimozione sono O(1).

## 7. Confronto delle implementazioni

| Rappresentazione | Dove si trova la cima? | Push | Pop | Memoria |
|---|---|---|---|---|
| Array senza shift, crescita a destra | `dati[top]`, ultimo occupato | O(1) | O(1) | Capacità fissa |
| Array senza shift, crescita a sinistra | `dati[top]`, primo occupato | O(1) | O(1) | Capacità fissa |
| Array con shift | Sempre `dati[0]` | O(n) | O(n) | Capacità fissa |
| Array con puntatore | `*(top-1)` | O(1) | O(1) | Capacità fissa |
| Lista semplice, cima in testa | Nodo indicato da `top` | O(1) | O(1) | Dinamica, un puntatore per nodo |
| Lista semplice, cima in coda | Ultimo nodo | O(1)* | O(n) | Dinamica |
| Lista doppia, cima in coda | Ultimo nodo | O(1) | O(1) | Dinamica, due puntatori per nodo |

*Per l'inserimento in coda O(1) occorre conservare il puntatore all'ultimo nodo, oltre al riferimento necessario alla lista. Le complessità sono quelle delle operazioni strutturali; l'allocazione dinamica ha un costo proprio.

**Osservazione:** lo shift non è richiesto dalla definizione di pila; dipende dalla rappresentazione scelta. L'ADT resta lo stesso anche quando cambiano le prestazioni.

---

# Parte II — Dalle pile di interi ai template

## 8. Perché introdurre i template?

Se sostituiamo `int` con `double` o `std::string`, il comportamento LIFO non cambia. Scrivere una classe separata per ogni tipo duplicherrebbe il codice. Un **template di classe** descrive una famiglia di classi parametrizzata dal tipo `T`.

## 9. Template di pila con array fisso

```cpp
#pragma once

template <typename T, int CAP = 10>
class PilaArray {
private:
    T dati[CAP];
    int top;

public:
    PilaArray() : top(-1) {}

    bool Empty() const { return top == -1; }

    bool Push(const T& valore) {
        if (top == CAP - 1) return false;
        dati[++top] = valore;
        return true;
    }

    bool Top(T& valore) const {
        if (Empty()) return false;
        valore = dati[top];
        return true;
    }

    bool Pop(T& valore) {
        if (Empty()) return false;
        valore = dati[top--];
        return true;
    }
};
```

Esempi d'uso:

```cpp
PilaArray<int, 5> numeri;
PilaArray<char, 20> parentesi;
PilaArray<std::string> parole; // CAP = 10, valore predefinito.
```

`T` è un **parametro di tipo**, `CAP` un **parametro intero**. Questa versione richiede che `T` sia costruibile senza argomenti e assegnabile; non è un contenitore generico completo come quelli della STL. I metodi del template sono definiti nell'header perché il compilatore deve vederne le definizioni quando istanzia il template.

## 10. Template di pila con nodi

```cpp
#pragma once

template <typename T>
class PilaNodi {
private:
    struct Nodo {
        T valore;
        Nodo* prossimo;
    };
    Nodo* top;

public:
    PilaNodi() : top(nullptr) {}
    PilaNodi(const PilaNodi&) = delete;
    PilaNodi& operator=(const PilaNodi&) = delete;

    ~PilaNodi() {
        while (!Empty()) {
            Nodo* vecchio = top;
            top = top->prossimo;
            delete vecchio;
        }
    }

    bool Empty() const { return top == nullptr; }

    bool Push(const T& valore) {
        top = new Nodo{valore, top};
        return true;
    }

    bool Top(T& valore) const {
        if (Empty()) return false;
        valore = top->valore;
        return true;
    }

    bool Pop(T& valore) {
        if (Empty()) return false;
        Nodo* vecchio = top;
        valore = vecchio->valore;
        top = vecchio->prossimo;
        delete vecchio;
        return true;
    }
};
```

La struttura dei nodi è la stessa della versione a interi: cambia soltanto il tipo del valore. Anche questa implementazione **non supporta la copia** ed è intenzionalmente semplificata. Il distruttore elimina tutti i nodi senza richiedere che `T` abbia un costruttore predefinito. L'assegnamento al parametro di uscita richiede comunque che `T` sia assegnabile.

## 11. Confronto con `std::stack`

```cpp
#include <stack>
#include <string>

std::stack<int> numeri;
numeri.push(10);
numeri.push(20);

if (!numeri.empty()) {
    int ultimo = numeri.top();
    numeri.pop();
}

std::stack<std::string> parole;
parole.push("informatica");
```

`std::stack<T>` è un **adattatore di contenitore** della libreria standard. Di norma utilizza `std::deque<T>` come contenitore sottostante; può essere configurato anche con altri contenitori compatibili, come `std::vector<T>` o `std::list<T>`. Offre `push`, `top`, `pop`, `empty`, `size` ed altre operazioni, ma non permette di accedere direttamente agli elementi intermedi.

La nostra `Pop(T&)` unisce lettura e rimozione; la STL separa le due operazioni: **`top()` legge, `pop()` rimuove**. Non si deve scrivere `int x = pila.pop();`.

**Nel progetto P3** è preferibile `std::stack<Modifica>`: è già collaudata, gestisce il contenitore sottostante ed evita di introdurre errori di memoria in un esercizio il cui obiettivo principale è la cronologia degli annullamenti. Le implementazioni manuali servono a comprendere l'ADT e i compromessi progettuali.

## 12. Proposte di laboratorio e domande

1. Disegnare il contenuto degli array dopo `Push(10)`, `Push(20)`, `Push(30)`, `Pop` nelle tre implementazioni delle sezioni 2, 3 e 4.
2. Perché nel vettore con shift il ciclo di `Push` deve procedere da destra verso sinistra?
3. Nella versione con indice, quale valore indica una pila vuota? E nella versione con puntatore alla prossima cella libera?
4. Se l'array ha capacità 5 e contiene tre elementi, quante assegnazioni agli elementi richiede `Push(40)` nella versione con shift? E senza shift?
5. Disegnare i puntatori `top`, `nuovo` e `daEliminare` durante un `Push` e un `Pop` con nodi.
6. Spiegare perché copiare soltanto il puntatore `top` di una pila a nodi è pericoloso.
7. Modificare `PilaArray<int, 5>` in `PilaArray<char, 5>`: quali righe della classe cambiano?
8. Confrontare la complessità di `Pop` con cima in testa e in coda di una lista semplicemente collegata.
9. Quale implementazione sceglieresti per una pila con massimo cinque elementi? E per una pila la cui dimensione massima non è nota?
10. Perché nel motore degli scambi P3 usiamo `std::stack<Modifica>` anziché una delle classi costruite in questa dispensa?

## 13. Riepilogo

- **ADT** = comportamento osservabile; **implementazione** = rappresentazione interna.
- Con un **indice top mobile**, l'array evita lo shift e permette `Push` e `Pop` in O(1).
- Con la **cima fissata in `dati[0]`**, lo shift costa O(n).
- Un **puntatore** può indicare una cella di array oppure un nodo: sono soluzioni diverse.
- Con **nodi collegati**, tenere `top` alla testa permette `Push` e `Pop` in O(1).
- I **template** generalizzano il tipo degli elementi senza duplicare l'algoritmo.
- In un'applicazione reale è normalmente opportuno preferire **`std::stack`** a una pila artigianale, salvo esigenze specifiche.
