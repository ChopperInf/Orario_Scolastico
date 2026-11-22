# P3 — La pila e l'annullamento degli scambi

Percorso per la classe quarta Informatica. La P3 introduce l'ADT pila e `std::stack` a partire dal motore P2, senza modificare la versione precedente.

## Materiali
- [Dispensa teorica](P3_Dispensa_Teorica.md)
- [Approfondimento: implementazioni della pila con array, shift, puntatori e template](P3_Approfondimento_Implementazioni_Pila.md)
- [Presentazione del docente (scaletta Markdown)](P3_Presentazione_Docente.md)
- Presentazione PowerPoint: file `P3_Presentazione_Docente.pptx` generato separatamente; caricamento nel repository ancora da effettuare.
- [Guida di laboratorio studenti](P3_Guida_Laboratorio.md)
- [Eserciziario](P3_Esercizi.md)
- [Soluzioni dell'eserciziario](P3_Soluzioni_Esercizi.md)
- [Piano dei test](P3_Test.md)

## Requisiti
La cronologia e' interna a `MotoreScambi`; ogni `Modifica` conserva due `Posizione`. Soltanto gli scambi riusciti sono registrati. L'annullamento usa i vincoli correnti e controlla lo stato finale, anche se quello iniziale non e' valido. Un annullamento rifiutato lascia invariati orario e pila. Un annullamento riuscito rimuove un solo elemento e non viene registrato.

## Codice
[Progetto docente P3](../../OrarioDocenteCPP_P3/). Il progetto degli studenti riguarda l'orario di una classe e conserva le sue regole specifiche.

## Stato della fase

**P3 conclusa sul piano funzionale:** compilazione ed esecuzione del progetto C++ confermate dall'utente. L'eserciziario contiene 13 esercizi, inclusi duplicazione di una pila, eliminazione in posizione x ed eliminazione dei numeri pari. La presentazione PowerPoint e' stata preparata come file scaricabile separato; la sua pubblicazione su GitHub e' ancora da completare.
