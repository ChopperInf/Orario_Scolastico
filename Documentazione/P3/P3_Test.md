# Test P3 — casi di accettazione

| Caso | Procedura | Atteso |
|---|---|---|
| T1 | Pila vuota, menu 9 | Rifiuto, orario invariato |
| T2 | Limite 7, scambio Lun 1 ↔ Lun 2, annulla | Ripristino |
| T3 | Limite 7, scambi Lun 1 ↔ Lun 2 e Mar 1 ↔ Mar 2, due annullamenti | LIFO, orario originale |
| T4 | Limite 7, tentare scambio Lun 2 ↔ Ven 8 | Rifiuto, nessuna registrazione |
| T5 | Scambio valido, poi limite 4, annulla | Rifiuto; pila e orario invariati |
| T6 | Dopo T5, limite 7, annulla | Successo, pop solo ora |
| T7 | Stato iniziale non valido, annullamento con stato finale valido | Successo |
| T8 | Tentare Scambia con due posizioni identiche | Rifiuto |
| T9 | Motore senza vincoli | Scambi rifiutati |

**Nota T7:** costruire un orario apposito e un vincolo modificabile, oppure configurare una successione di scambi che produca un orario non valido dopo la variazione del limite, ma il cui stato precedente rispetti il limite aggiornato. La prova non deve richiedere di alterare direttamente la pila.
