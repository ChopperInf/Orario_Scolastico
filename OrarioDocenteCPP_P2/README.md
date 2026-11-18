# OrarioDocenteCPP_P2 — vincoli e tessere polimorfiche

Prototipo console **C++17**, evoluzione di P1, con due percorsi didattici: **P2-A (vincoli astratti)** e **P2-B (tessere polimorfiche)**. I sorgenti di P1 non vengono modificati.

## Aprire ed eseguire i progetti

Aprire `OrarioDocenteCPP_P2.sln` in Visual Studio 2022 (MSVC v143, C++17, piattaforma **x64**). La soluzione contiene due eseguibili:

| Progetto | Scopo | Tracce dei costruttori/distruttori |
| --- | --- | --- |
| `OrarioDocenteCPP_P2` | Applicazione console completa | **Sempre disattivate**, anche in configurazione Visual Studio Debug |
| `DebugPolimorfismo_P2` | Esercizio autonomo con matrice 2×2 e due vincoli | Attivabili/disattivabili con una riga |

In Esplora soluzioni fare clic destro sul progetto desiderato e scegliere **Imposta come progetto di avvio**. Compilare ed eseguire con Ctrl+F5. I due progetti compilano **gli stessi file .cpp del modello e dei vincoli**; non esistono copie delle classi.

## P2-A — Vincoli polimorfici

`Engine/Vincolo.h` definisce una **classe astratta** con `Verifica(Orario&)` e `GetMessaggio()` virtuali puri (`= 0`) e distruttore virtuale. Non è possibile istanziare direttamente `Vincolo`.

- `VincoloSenzaBuchi`: vieta ore vuote **tra** lezioni dello stesso giorno (le ore libere iniziali e finali sono ammesse).
- `VincoloMaxOreGiornaliere`: limita il numero di lezioni per giorno; limite iniziale **4**, modificabile da menu tra 1 e 8.
- `MotoreScambi`: memorizza `std::vector<Vincolo*>`, verifica l'orario prima e dopo uno scambio e annulla lo scambio se un vincolo non è rispettato.
- `InterfacciaConsole`: **possiede** i due oggetti vincolo; `MotoreScambi` conserva solo puntatori **non proprietari** e non li elimina.

Il controllo avviene tramite puntatori alla classe base, che richiamano il metodo `Verifica()` della classe derivata. Il limite 4 rende l'orario di esempio inizialmente non valido: per provare gli scambi impostare prima 7 o 8 con l'opzione 8.

## P2-B — Tessere polimorfiche

`Tessera` è una classe base **concreta e polimorfica**: contiene `materia`, `classe`, `aula`, offre i getter, `virtual GetDescrizione()` **non puro** e un **distruttore virtuale**. È possibile creare una `Tessera` direttamente.

- `TesseraAula` deriva da `Tessera` e ridefinisce `GetDescrizione()` con `override`.
- `TesseraLaboratorio` deriva da `Tessera`, aggiunge `tipoLaboratorio`, `docenteITP` e un puntatore opzionale `DotazioneLabInformatica*`. Ridefinisce `GetDescrizione()` e il distruttore con `override`.
- `DotazioneLabInformatica` memorizza `vector<string> postazioni` e `bool presenzaLIM`. Per un laboratorio senza dotazione informatica il puntatore è `nullptr`.
- `TesseraLaboratorio` **possiede** la dotazione ricevuta e la elimina nel proprio distruttore. Copia e assegnamento sono disabilitati con `= delete`, per evitare la doppia liberazione.
- `Orario` contiene `Tessera* celle[5][8]` e **possiede** le tessere inserite con `Set()`; le elimina nel distruttore. `Get()` restituisce un puntatore **non proprietario**.

Una chiamata `tessera->GetDescrizione()` tramite `Tessera*` utilizza l'implementazione del tipo effettivo. Analogamente, `delete` tramite `Tessera*` richiama prima il distruttore della derivata, poi quello della base: è il motivo per cui `~Tessera()` è virtuale. Il modello e il motore degli scambi rimangono compatibili con tessere di tipi diversi.

## Debug didattico: costruttori, distruttori e polimorfismo

Le macro sono definite in **`DebugP2.h`**, incluso nei sorgenti interessati. **Per disattivare i messaggi nel solo progetto didattico**, commentare questa unica riga:

```cpp
#define ABILITA_DEBUG_P2
```

Per riattivarli, togliere il commento e **ricompilare**. I messaggi sono scritti su `std::cerr` e identificano classe, operazione e indirizzo `this`. Se disattivati, le macro non producono istruzioni di stampa.

**Isolamento garantito:** il progetto didattico definisce `PROGETTO_DEBUG_P2` nelle proprie impostazioni del preprocessore; quello normale **non** lo definisce. Il debug didattico richiede **entrambe** le definizioni. Pertanto `OrarioDocenteCPP_P2` non stampa mai questi messaggi, neppure in configurazione Visual Studio **Debug|x64**. La parola «Debug» di Visual Studio non è l'interruttore dei messaggi didattici.

### Esercizio A — matrice 2×2

Il file `Debug/main_debug.cpp` alloca quattro oggetti in `Tessera* matrice[2][2]`:

| Cella | Tipo effettivo |
| --- | --- |
| `[0][0]` | `Tessera` |
| `[0][1]` | `TesseraAula` |
| `[1][0]` | `TesseraLaboratorio` senza dotazione |
| `[1][1]` | `TesseraLaboratorio` con `DotazioneLabInformatica` |

Il programma mostra le descrizioni polimorfiche, poi elimina gli oggetti con due cicli annidati e imposta i puntatori a `nullptr`. **Attenzione:** nell'ultima cella la dotazione viene costruita prima della tessera di laboratorio, perché è creata con `new` come argomento del costruttore. Durante la distruzione, il laboratorio elimina la dotazione **prima** che sia eseguito il distruttore della classe base `Tessera`.

### Esercizio B — due vincoli astratti

Il programma crea `Vincolo* vincoli[2]` con `VincoloSenzaBuchi` e `VincoloMaxOreGiornaliere`, invoca `GetMessaggio()` e `Verifica()` attraverso i puntatori alla base su un orario vuoto, quindi elimina entrambi gli oggetti. L'orario vuoto rispetta entrambi i vincoli.

### Ordine dei messaggi atteso

| Oggetto | Costruzione | Distruzione |
| --- | --- | --- |
| `TesseraAula` | `Tessera` → `TesseraAula` | `TesseraAula` → `Tessera` |
| `TesseraLaboratorio` con dotazione | `DotazioneLabInformatica` → `Tessera` → `TesseraLaboratorio` | `TesseraLaboratorio` → `DotazioneLabInformatica` → `Tessera` |
| `VincoloMaxOreGiornaliere` | `Vincolo` → `VincoloMaxOreGiornaliere` | `VincoloMaxOreGiornaliere` → `Vincolo` |

I **costruttori non sono virtuali**. Il distruttore virtuale permette la distruzione corretta attraverso un puntatore alla base. Non eliminare `virtual` dal distruttore della base per fare esperimenti: eliminare una derivata tramite un puntatore alla base senza distruttore virtuale provoca comportamento indefinito.

## Casi di prova manuali del programma normale

L'orario iniziale contiene 7 lezioni dal lunedì al giovedì e 6 il venerdì.

1. **Scambio valido:** impostare il limite a 7, poi scambiare lunedì ora 1 con lunedì ora 2.
2. **Buco:** con limite 7, scambiare lunedì ora 2 con venerdì ora 8: lo scambio deve essere rifiutato e annullato.
3. **Massimo ore:** con limite 7, scambiare venerdì ora 6 con lunedì ora 8: lunedì raggiungerebbe 8 lezioni e lo scambio deve essere rifiutato.
4. **Verifica iniziale:** con limite 4 l'orario non è valido; impostando 7 entrambi i vincoli risultano rispettati.

Il nuovo limite ha effetto immediato, ma non viene salvato su file.

## Documentazione

- [Scheda didattica P2](../Documentazione/P2/P2_Scheda_Didattica.md)
- [P2-A — dispensa teorica sui vincoli](../Documentazione/P2/P2_Dispensa_Teorica.md)
- [P2-B — dispensa teorica sulle tessere](../Documentazione/P2/P2_Dispensa_Teorica_Tessere_Polimorfiche.md)
- [Approfondimento: metodi virtuali, classi astratte e distruttori](../Documentazione/P2/P2_Approfondimento_Metodi_Virtuali_Classi_Astratte_Cpp.md)
- [Guida di laboratorio](../Documentazione/P2/P2_Guida_Laboratorio.md)
- [Esercizi](../Documentazione/P2/P2_Esercizi.md) e [soluzioni](../Documentazione/P2/P2_Soluzioni_Esercizi.md)

Nella cartella `Documentazione/P2` sono presenti anche le presentazioni PowerPoint per P2-A e P2-B.
