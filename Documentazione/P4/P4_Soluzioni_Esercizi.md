# P4 — Soluzioni ragionate dell'eserciziario

## Soluzione 1
Estrazioni: A, B. Coda finale: C, D (C in testa).

## Soluzione 2
```cpp
#include <iostream>
#include <queue>
int main() {
    std::queue<int> q;
    for (int i = 1; i <= 5; ++i) q.push(i);
    std::cout << "Primo: " << q.front() << " Numero: " << q.size() << '\n';
    while (!q.empty()) { std::cout << q.front() << ' '; q.pop(); }
}
```

## Soluzione 3
```cpp
std::queue<int> clienti;
for (int numero = 1; numero <= 5; ++numero) clienti.push(numero);
while (!clienti.empty()) {
    int chiamato = clienti.front();
    clienti.pop();
    // Visualizzare il cliente chiamato nell'interfaccia.
}
```

## Soluzione 4
```cpp
std::queue<int> Duplica(std::queue<int> originale) {
    std::queue<int> copia;
    while (!originale.empty()) {
        copia.push(originale.front());
        originale.pop();
    }
    return copia;
}
```
La copia per valore impedisce che le rimozioni modifichino la coda del chiamante.

## Soluzione 5
```cpp
std::queue<int> RimuoviPosizione(std::queue<int> q, int x) {
    std::queue<int> risultato;
    int posizione = 0;
    while (!q.empty()) {
        if (posizione != x) risultato.push(q.front());
        q.pop();
        ++posizione;
    }
    return risultato;
}
```
Per `x < 0` o `x >= size` nessun elemento e' rimosso.

## Soluzione 6
```cpp
std::queue<int> SenzaPari(std::queue<int> q) {
    std::queue<int> risultato;
    while (!q.empty()) {
        if (q.front() % 2 != 0) risultato.push(q.front());
        q.pop();
    }
    return risultato;
}
```

## Soluzione 7
```cpp
int Somma(std::queue<int> q) {
    int totale = 0;
    while (!q.empty()) { totale += q.front(); q.pop(); }
    return totale;
}
```
Costo temporale O(n), memoria aggiuntiva O(n) dovuta alla copia per valore.

## Soluzione 8
```cpp
#include <stack>
std::queue<int> Inverti(std::queue<int> q) {
    std::stack<int> pila;
    while (!q.empty()) { pila.push(q.front()); q.pop(); }
    std::queue<int> risultato;
    while (!pila.empty()) { risultato.push(pila.top()); pila.pop(); }
    return risultato;
}
```
La pila inverte l'ordine, la coda risultante lo conserva nelle estrazioni successive.

## Soluzione 9
```cpp
std::queue<int> urgenti, ordinarie;
while (!urgenti.empty() || !ordinarie.empty()) {
    std::queue<int>& scelta = !urgenti.empty() ? urgenti : ordinarie;
    int richiesta = scelta.front();
    scelta.pop();
    // Elaborare richiesta.
}
```
Le richieste urgenti sopravanzano quelle ordinarie, quindi non esiste un unico ordine FIFO globale.

## Soluzione 10
Richiesta appena ricevuta: coda. Scambio rifiutato: rimosso dalla coda, non inserito nella pila. Scambio riuscito: richiesta rimossa e `Modifica` inserita nella pila. Annullamento riuscito: rimozione della modifica in cima alla pila, senza nuova richiesta.

## Soluzione 11
Attributo privato `std::queue<RichiestaScambio>`; metodi `Accoda`, `Vuota`, `NumeroRichieste`, `ElaboraPrima`. Il gestore delega il tentativo al motore per preservare un'unica implementazione dei vincoli.

## Soluzione 12
Si usa il limite **corrente** al momento dell'elaborazione. Se R1 e' rifiutata, viene rimossa; orario e pila non cambiano. R2 resta in attesa.

## Soluzione 13
Esempio: accodare R1 e R2; eseguire uno scambio immediato S; elaborare R1; annullare l'ultimo scambio riuscito; elaborare R2. La coda continua nell'ordine R1→R2. La pila contiene soltanto le modifiche riuscite e l'annullamento riguarda la sua cima. Gli esiti concreti dipendono dai vincoli e dalle celle scelte.

## Soluzione 14
`front()` e `pop()` su coda vuota hanno precondizione violata: controllare prima `empty()`. `pop()` restituisce `void`: leggere `front()` in una variabile e poi chiamare `pop()`.
