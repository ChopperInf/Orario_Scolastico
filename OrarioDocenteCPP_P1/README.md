# OrarioClasseCPP_P0

Progetto C++ console della fase P0, percorso autonomo degli studenti.
La guida e' in `Documentazione/P0/P0_Guida_Laboratorio.md` nella radice del repository.

Aprire `OrarioClasseCPP_P0.sln` con Visual Studio 2022 (Desktop development with C++),
selezionare Debug|x64 e avviare con Ctrl+F5.

- `Model`: Tessera (materia, docente, aula), Posizione, Orario con matrice di puntatori 5 x 8.
- `Engine`: validazione senza buchi e scambio con ripristino.
- `InterfacciaConsole`: menu, input e stampa.
- `DatiEsempio`: caricamento di lezioni fittizie.
- `main.cpp`: solo avvio e composizione degli oggetti.

Prove: visualizzazione 5x8; lunedi' prima ora occupata e ottava libera;
scambio ore 1 e 2 consentito; scambio ore 1 e 8 rifiutato e ripristinato;
verifica senza buchi.

`Orario` possiede le tessere accettate da `Set`; se `Set` restituisce false
il chiamante deve eliminare la tessera. La copia di `Orario` e' disabilitata.
