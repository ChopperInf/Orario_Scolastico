# P3 — Soluzioni ragionate dell'eserciziario

## E1
Dopo le operazioni: `[4]`, `[4,9]`, `[4]`, `[4,2]`, `[4,2,7]`, `[4,2]` (da fondo a cima). `top() == 2`, `size() == 2`. Su pila vuota `top()` non e' valido: controllare `empty()` prima.

## E2
```cpp
#include <stack>
#include <string>
std::string Inverti(const std::string& testo) {
    std::stack<char> pila;
    for (char c : testo) pila.push(c);
    std::string risultato;
    while (!pila.empty()) {
        risultato += pila.top();
        pila.pop();
    }
    return risultato;
}
```

## E3
```cpp
#include <stack>
#include <string>
bool Bilanciate(const std::string& testo) {
    std::stack<char> pila;
    for (char c : testo) {
        if (c == '(') pila.push(c);
        if (c == ')') {
            if (pila.empty()) return false;
            pila.pop();
        }
    }
    return pila.empty();
}
```

## E4
```cpp
#include <stack>
#include <string>
bool BilanciateTreTipi(const std::string& testo) {
    std::stack<char> pila;
    for (char c : testo) {
        if (c == '(' || c == '[' || c == '{') pila.push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (pila.empty()) return false;
            char aperta = pila.top();
            if ((c == ')' && aperta != '(') ||
                (c == ']' && aperta != '[') ||
                (c == '}' && aperta != '{')) return false;
            pila.pop();
        }
    }
    return pila.empty();
}
```
`([)]` contiene lo stesso numero di aperture e chiusure ma l'ordine e' errato.

## E5
Prima di ogni aggiunta eseguire `cronologia.push(frase)`; poi aggiornare `frase`. Per annullare: se `empty()` restituire errore; altrimenti `frase = cronologia.top(); cronologia.pop();`. L'annullamento non produce una nuova registrazione.

## E6
```cpp
#include <stack>
#include <string>
std::string Binario(unsigned int numero) {
    if (numero == 0) return "0";
    std::stack<int> cifre;
    while (numero > 0) {
        cifre.push(numero % 2);
        numero /= 2;
    }
    std::string risultato;
    while (!cifre.empty()) {
        risultato += char('0' + cifre.top());
        cifre.pop();
    }
    return risultato;
}
```
Risultati: 1 → 1; 13 → 1101; 32 → 100000; 0 → 0.

## E7
```cpp
#include <stack>
#include <sstream>
#include <string>
bool ValutaPostfissa(const std::string& espressione, int& risultato) {
    std::stack<int> pila;
    std::istringstream input(espressione);
    std::string token;
    while (input >> token) {
        if (token == "+" || token == "-" || token == "*") {
            if (pila.size() < 2) return false;
            int destra = pila.top(); pila.pop();
            int sinistra = pila.top(); pila.pop();
            if (token == "+") pila.push(sinistra + destra);
            if (token == "-") pila.push(sinistra - destra);
            if (token == "*") pila.push(sinistra * destra);
        } else {
            std::istringstream numero(token);
            int valore;
            char resto;
            if (!(numero >> valore) || (numero >> resto)) return false;
            pila.push(valore);
        }
    }
    if (pila.size() != 1) return false;
    risultato = pila.top();
    return true;
}
```
Assumere che le operazioni intere non producano overflow. Test: `3 4 + 2 *` → 14; `5 2 -` → 3; `+` → errore; `1 2` → errore.

## E8
La pila risiede nel motore degli scambi. Lo scambio riuscito chiama `push(Modifica(prima, seconda))`. L'annullamento legge `top()`, tenta lo scambio inverso, verifica lo stato **finale** con i vincoli correnti e chiama `pop()` solo se la verifica riesce. Se fallisce, lo scambio temporaneo viene invertito e la pila rimane invariata. Il codice del docente e' consultabile in `OrarioDocenteCPP_P3/Engine`, ma i vincoli dell'orario di classe restano differenti.

## E9
No: B non e' in cima alla pila. Occorre modificare il vincolo in modo che l'annullamento di C produca uno stato valido e poi riprovare. Non si elimina C in caso di rifiuto.

## E10
Cronologia: LIFO; richieste di assistenza: FIFO; parentesi: LIFO; lavori di stampa nell'ordine di invio: FIFO. La coda sara' affrontata nella P4.

## E11 — Duplicare una pila
La prima pila ausiliaria inverte temporaneamente l'ordine; trasferendo gli elementi alla copia e contemporaneamente ripristinando l'originale si conserva la sequenza iniziale.
```cpp
#include <stack>
void Duplica(std::stack<int>& originale, std::stack<int>& copia) {
    if (&originale == &copia) return; // Stessa pila: e' gia' identica.
    while (!copia.empty()) copia.pop();
    std::stack<int> ausiliaria;
    while (!originale.empty()) {
        ausiliaria.push(originale.top());
        originale.pop();
    }
    while (!ausiliaria.empty()) {
        int valore = ausiliaria.top();
        ausiliaria.pop();
        originale.push(valore);
        copia.push(valore);
    }
}
```
Se l'originale e' [2, 5, 8] dal fondo alla cima, la copia e' [2, 5, 8] e l'originale resta invariata. La soluzione e' intenzionalmente basata sulle operazioni della pila, anche se `std::stack` supporta la copia diretta.

## E12 — Eliminare l'elemento in posizione x
```cpp
#include <stack>
bool EliminaInPosizione(std::stack<int>& pila, int x) {
    if (x < 0 || static_cast<size_t>(x) >= pila.size()) return false;
    std::stack<int> ausiliaria;
    for (int i = 0; i < x; i++) {
        ausiliaria.push(pila.top());
        pila.pop();
    }
    pila.pop(); // Elimina l'elemento in posizione x.
    while (!ausiliaria.empty()) {
        pila.push(ausiliaria.top());
        ausiliaria.pop();
    }
    return true;
}
```
Esempio: [10, 20, 30, 40] dal fondo alla cima; con `x = 2` viene eliminato 20 e rimane [10, 30, 40]. Per una posizione non valida la pila non viene toccata.

## E13 — Eliminare tutti i numeri pari
```cpp
#include <stack>
void EliminaPari(std::stack<int>& pila) {
    std::stack<int> ausiliaria;
    while (!pila.empty()) {
        int valore = pila.top();
        pila.pop();
        if (valore % 2 != 0) ausiliaria.push(valore);
    }
    while (!ausiliaria.empty()) {
        pila.push(ausiliaria.top());
        ausiliaria.pop();
    }
}
```
Esempio: [1, 4, 3, 0, -5, 8] dal fondo alla cima diventa [1, 3, -5]. Il secondo trasferimento e' indispensabile per ripristinare l'ordine relativo dei dispari. In tutti e tre gli esercizi il costo temporale e' O(n) e lo spazio ausiliario e' O(n) nel caso peggiore.
