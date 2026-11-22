# P3 — Presentazione del docente
*Scaletta pronta per la proiezione: una sezione corrisponde a una diapositiva.*

---

## 1. Situazione iniziale
Il motore P2 scambia due celle e verifica i vincoli. Come recuperiamo la modifica precedente dopo tre scambi riusciti?

---

## 2. Esperimento con tre modifiche
A → B → C. Per tornare indietro: annullare C, poi B, poi A. Non possiamo annullare A saltando C e B.

---

## 3. LIFO
Last In, First Out. Esempio concreto: pila di piatti. Solo l'elemento in cima e' immediatamente accessibile.

---

## 4. L'ADT
L'interfaccia descrive **cosa** si puo' fare, non **come** e' memorizzato il contenitore.

---

## 5. La libreria STL
`#include <stack>`; `std::stack<int> pila;`. Operazioni: `push`, `top`, `pop`, `empty`.

---

## 6. Attenzione a pop
`pop()` elimina senza restituire. Prima si consulta `top()`, poi si elimina con `pop()`, solo se `empty()` e' falso.

---

## 7. Esempio alla lavagna
`push(3)`, `push(8)`, `pop()`, `push(5)`: qual e' la cima? Risposta: 5. Quali elementi restano? 3 e 5.

---

## 8. Dalla pila alla cronologia
`std::stack<Modifica>` nel motore. `Modifica` conserva le due posizioni. Uno scambio e' il proprio inverso.

---

## 9. Quando eseguire push?
Soltanto dopo uno scambio autorizzato. Uno scambio rifiutato non e' una modifica da annullare.

---

## 10. Quando eseguire pop?
Soltanto dopo un annullamento autorizzato. `top()` non deve eliminare la modifica prima della verifica.

---

## 11. I vincoli possono cambiare
Uno scambio passato puo' non essere piu' annullabile. Si verifica il risultato con i vincoli correnti, non con quelli storici.

---

## 12. Caso particolare
L'orario di partenza e' non valido dopo un cambio di limite. Se l'annullamento produce un orario valido, e' consentito.

---

## 13. Esercizio classico
Verificare parentesi `() [] {}`: ogni apertura entra nella pila; ogni chiusura deve corrispondere alla cima. `([)]` e' errata.

---

## 14. Verifica finale
Due scambi, due annullamenti, pila vuota, annullamento rifiutato e successivo tentativo dopo modifica del vincolo.

---

## 15. Verso P4
P3: cronologia LIFO. P4: richieste FIFO. Stessi concetti di ADT, comportamento differente.
