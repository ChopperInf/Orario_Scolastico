# OrarioDocenteCPP_P3 — annullamento con pila

Progetto C++17 per Visual Studio 2022 (MSVC v143, x64), derivato da P2. Aprire `OrarioDocenteCPP_P3.sln`, selezionare Debug|x64 o Release|x64 e avviare con Ctrl+F5.

## Novita'
- `Engine/Modifica.h`: memorizza le due posizioni dello scambio.
- `MotoreScambi`: contiene `std::stack<Modifica>` e offre `Annulla`.
- Menu opzione **9**: annullamento dell'ultimo scambio.
- Gli scambi ordinari controllano stato iniziale e finale; l'annullamento controlla il solo stato finale con i vincoli correnti.
- Un annullamento rifiutato non modifica ne' orario ne' pila.
- Il motore si associa al primo orario modificato; non va riutilizzato per un altro orario.
- Il debug didattico P2 rimane disattivato nel progetto normale.

## Prova manuale
1. Avviare: il limite iniziale e' 4 e l'orario dimostrativo non e' valido.
2. Menu 8: impostare 7.
3. Menu 3: scambiare lunedi' ore 1 e 2.
4. Menu 3: scambiare martedi' ore 1 e 2.
5. Menu 9 due volte: si ripristina l'orario originale; una terza volta segnala pila vuota.
6. Ripetere uno scambio valido; impostare il limite a 4; menu 9: l'annullamento e' rifiutato e rimane in pila.
7. Impostare il limite a 7; menu 9: l'annullamento riesce.

## Limiti didattici
Il caricamento iniziale con `Orario::Set` avviene prima delle modifiche. Durante l'esecuzione tutte le modifiche ordinarie passano dal motore; chiamate esterne a `ScambiaCelle` invaliderebbero il significato della cronologia. La versione P2 rimane invariata.

[Documentazione P3](../Documentazione/P3/README.md).
