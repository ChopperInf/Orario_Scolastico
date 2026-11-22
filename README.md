# Progetto Orario scolastico

Progetto didattico di Informatica per rappresentare e modificare l'orario settimanale di una classe, applicando la programmazione a oggetti e la separazione tra **Model**, **Engine** e **interfaccia**.

## Obiettivo e percorso di sviluppo

L'obiettivo generale è arrivare a un programma capace di esaminare un orario esistente e proporre o verificare modifiche nel rispetto dei vincoli stabiliti per la gestione dell'orario scolastico.

Il **primo prototipo** affronta volutamente un problema più limitato: consente di scambiare due celle di un orario settimanale e accetta lo scambio soltanto se non produce ore vuote prima di lezioni successive nella stessa giornata. Per ora non vengono controllati conflitti tra docenti, disponibilità delle aule o altri vincoli organizzativi.

Il percorso didattico previsto è:

1. **Analisi e progettazione:** studio del problema, del vincolo «senza buchi», delle classi e della gestione della memoria.
2. **Prototipo C++ Console:** applicazione delle conoscenze su classi, puntatori, riferimenti e memoria dinamica; implementazione autonoma dei metodi delle classi e verifica del programma attraverso un menu testuale.
3. **Versione C# con interfaccia WPF:** studio e sviluppo della rappresentazione grafica dell'orario e dell'interazione con l'utente, mantenendo la distinzione tra Model, Engine e interfaccia.
4. **Evoluzioni successive:** ampliamento dei vincoli e dei criteri di valutazione dell'orario, da definire nelle fasi successive del progetto.

Le cartelle C++ e C# rappresentano **due implementazioni distinte**. Il repository contiene già un prototipo C# funzionante; la sequenza indicata sopra descrive invece il percorso didattico da seguire.

## Organizzazione del repository

```text
orario_scolastico/
|
+-- Documentazione/        Documenti di analisi, progettazione e dispense
|
+-- OrarioScolasticoCPP/   Primo prototipo C++ con interfaccia Console
|   +-- Model/            Tessera, Posizione, Orario
|   +-- Engine/           ValidatoreOrario, MotoreScambi
|   +-- main.cpp          Menu e funzioni dell'interfaccia Console
|
+-- OrarioClasse/          Applicazione C# con interfaccia WPF
|   +-- Model/
|   +-- Engine/
|   +-- MainWindow.xaml
|   +-- MainWindow.xaml.cs
|
+-- OrarioClasse.sln       Soluzione Visual Studio della versione C#
+-- README.md
```

### Documentazione

La cartella [Documentazione](Documentazione/) raccoglie le dispense e i documenti di progetto.

Per iniziare il lavoro in C++, consultare [Analisi e progettazione del primo prototipo C++](Documentazione/ANALISI_E_PROGETTAZIONE_ORARIO_SCOLASTICO_CPP_STUDENTI_REVISIONE.md), che descrive requisiti, architettura, classi, puntatori, gestione della memoria, fasi di sviluppo e casi di prova.

### Prototipo C++ Console

La cartella [OrarioScolasticoCPP](OrarioScolasticoCPP/) contiene:

- **Model:** `Tessera.h`, `Posizione.h`, `Orario.h`.
- **Engine:** `ValidatoreOrario.h`, `MotoreScambi.h`.
- **Interfaccia:** `main.cpp` completo, con caricamento dell'orario di esempio, visualizzazione, consultazione delle celle, richiesta di scambio e verifica della validità.

L'orario è rappresentato da una matrice `Tessera* celle[5][8]`. Le tessere sono oggetti creati dinamicamente; le celle vuote contengono `nullptr`.

**Stato del prototipo C++:** i file `.h` e il `main.cpp` sono disponibili. Gli studenti devono realizzare i corrispondenti file `.cpp` delle classi del Model e dell'Engine. Fino al completamento di tali implementazioni, il programma non è ancora compilabile e collegabile come applicazione completa.

### Versione C# WPF

La cartella [OrarioClasse](OrarioClasse/) contiene il prototipo C# già presente nel repository, suddiviso in Model, Engine e interfaccia grafica WPF.

Questa versione permette di selezionare due celle dell'orario e tentare uno scambio; il motore conferma la modifica soltanto se il validatore non rileva ore vuote prima di lezioni successive.

## Versione C# — Configurazione ed esecuzione

Questa sezione conserva le indicazioni operative relative al prototipo C# originale.

**ORARIOCLASSE — WPF .NET Framework 4.8**

Aprire `OrarioClasse.sln` in Visual Studio 2022 su Windows.

Installare il carico di lavoro **Sviluppo di applicazioni desktop .NET** e il **targeting pack .NET Framework 4.8**.

Selezionare `OrarioClasse` come progetto di avvio e premere **F5**.

Il codice didattico riprende le tre dispense fornite. La differenza tecnica è il file di progetto classico `.csproj` per .NET Framework 4.8.

Non serve `Program.cs`: il punto di ingresso WPF è generato da `App.xaml`.

### Prove della versione C#

- Selezionare due celle occupate e premere **Scambia**: scambio autorizzato.
- Selezionare lunedì 7ª ora e venerdì 7ª ora vuota: scambio autorizzato.
- Selezionare lunedì 3ª ora e venerdì 7ª ora vuota: scambio rifiutato.

**Nota:** la compilazione dell'applicazione WPF richiede Visual Studio/MSBuild su Windows.


### Convenzione per i prototipi C++

Le versioni consolidate del progetto docente sono conservate in cartelle autonome `OrarioDocenteCPP_P1`, `OrarioDocenteCPP_P2`, ecc. Ogni fase contiene la propria soluzione Visual Studio (`.sln`) e il progetto (`.vcxproj`). La fase successiva parte da una copia della precedente, senza sovrascriverla.

## Approfondimenti P2

La fase P2 presenta due applicazioni del polimorfismo: [P2-A — vincoli](Documentazione/P2/P2_Dispensa_Teorica.md) e [P2-B — tessere di aula e laboratorio](Documentazione/P2/P2_Dispensa_Teorica_Tessere_Polimorfiche.md). La versione docente P2 contiene `TesseraAula`, `TesseraLaboratorio` e la dotazione informatica opzionale `DotazioneLabInformatica`; P0 e P1 restano versioni storiche autonome.


## Percorso C++ docente — P0, P1, P2, P3, P4

Il repository comprende prototipi didattici successivi e autonomi, con il codice del docente separato dalle attività degli studenti. La descrizione del primo prototipo nelle sezioni precedenti rimane come riferimento storico.

| Fase | Contenuto | Collegamento |
| --- | --- | --- |
| P2 | Vincoli e tessere polimorfiche | [OrarioDocenteCPP_P2](OrarioDocenteCPP_P2/) |
| **P3** | **Pila LIFO, cronologia degli scambi e annullamento** | [OrarioDocenteCPP_P3](OrarioDocenteCPP_P3/) |
| **P4** | **Coda FIFO, richieste di scambio e validazione differita** | [OrarioDocenteCPP_P4](OrarioDocenteCPP_P4/) |

La [documentazione P3](Documentazione/P3/) comprende dispensa teorica, presentazione docente in Markdown, guida di laboratorio, eserciziario con **13 esercizi**, soluzioni e piano dei test. La versione PowerPoint della presentazione è stata prodotta separatamente e deve ancora essere caricata nel repository.

**Stato P3:** compilazione ed esecuzione del progetto confermate dall'utente in Visual Studio; codice e materiali Markdown pubblicati. La versione P2 rimane invariata.


## Materiali P4

La [Documentazione/P4](Documentazione/P4/) comprende dispensa teorica, presentazione docente, guida laboratorio, eserciziario, soluzioni e piano test. La P4 e' in sviluppo sul ramo `p4-coda-richieste`; il prototipo P3 sul ramo principale resta invariato.
