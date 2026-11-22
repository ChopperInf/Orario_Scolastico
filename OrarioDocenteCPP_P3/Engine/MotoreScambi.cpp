#include "MotoreScambi.h"

void MotoreScambi::AggiungiVincolo(Vincolo* vincolo) {
    if (vincolo == nullptr) return;
    for (int i = 0; i < static_cast<int>(vincoli.size()); i++)
        if (vincoli[i] == vincolo) return;
    vincoli.push_back(vincolo);
}

bool MotoreScambi::VerificaVincoli(Orario& orario, std::string& messaggio) {
    if (vincoli.empty()) {
        messaggio = "nessun vincolo registrato";
        return false;
    }
    for (int i = 0; i < static_cast<int>(vincoli.size()); i++)
        if (!vincoli[i]->Verifica(orario)) {
            messaggio = vincoli[i]->GetMessaggio();
            return false;
        }
    return true;
}

// Tutte le modifiche alle celle del motore passano da questa logica comune.
bool MotoreScambi::EseguiScambio(Orario& orario, Posizione prima, Posizione seconda,
                                std::string& messaggio, bool verificaIniziale) {
    messaggio = "";
    if (prima.GetGiorno() < 0 || prima.GetGiorno() >= 5 ||
        prima.GetOra() < 0 || prima.GetOra() >= 8 ||
        seconda.GetGiorno() < 0 || seconda.GetGiorno() >= 5 ||
        seconda.GetOra() < 0 || seconda.GetOra() >= 8) {
        messaggio = "posizione non valida";
        return false;
    }
    if (prima.GetGiorno() == seconda.GetGiorno() &&
        prima.GetOra() == seconda.GetOra()) {
        messaggio = "le due posizioni coincidono";
        return false;
    }
    if (verificaIniziale && !VerificaVincoli(orario, messaggio)) {
        messaggio = "orario iniziale non valido: " + messaggio;
        return false;
    }
    orario.ScambiaCelle(prima, seconda);
    if (VerificaVincoli(orario, messaggio)) return true;
    orario.ScambiaCelle(prima, seconda); // Ripristino in caso di rifiuto.
    return false;
}

bool MotoreScambi::Scambia(Orario& orario, Posizione prima, Posizione seconda,
                          std::string& messaggio) {
    if (orarioCronologia != nullptr && orarioCronologia != &orario) {
        messaggio = "il motore e' associato a un altro orario";
        return false;
    }
    if (!EseguiScambio(orario, prima, seconda, messaggio, true)) return false;
    cronologia.push(Modifica(prima, seconda));
    orarioCronologia = &orario;
    return true;
}

bool MotoreScambi::Annulla(Orario& orario, std::string& messaggio) {
    if (cronologia.empty()) {
        messaggio = "nessuno scambio da annullare";
        return false;
    }
    if (orarioCronologia != &orario) {
        messaggio = "la cronologia appartiene a un altro orario";
        return false;
    }
    Modifica ultima = cronologia.top();
    if (!EseguiScambio(orario, ultima.GetPrima(), ultima.GetSeconda(), messaggio, false)) {
        messaggio = "annullamento non consentito: " + messaggio +
                   ". Modificare i vincoli e riprovare";
        return false;
    }
    cronologia.pop();
    messaggio = "ultimo scambio annullato";
    return true;
}
