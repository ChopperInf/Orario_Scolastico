#include "GestoreRichieste.h"

void GestoreRichieste::Accoda(const RichiestaScambio& richiesta) {
    richieste.push(richiesta);
}

bool GestoreRichieste::Vuota() const {
    return richieste.empty();
}

std::size_t GestoreRichieste::NumeroRichieste() const {
    return richieste.size();
}

EsitoRichiesta GestoreRichieste::ElaboraPrima(MotoreScambi& motore,
                                             Orario& orario,
                                             std::string& messaggio) {
    if (richieste.empty()) {
        messaggio = "Non ci sono richieste in attesa.";
        return EsitoRichiesta::CODA_VUOTA;
    }
    // front() consulta la richiesta piu' vecchia; non la rimuove.
    RichiestaScambio richiesta = richieste.front();
    // La validita' viene verificata ora, usando i vincoli correnti.
    bool riuscito = motore.Scambia(orario, richiesta.GetPrima(),
                                  richiesta.GetSeconda(), messaggio);
    // Una richiesta elaborata esce sempre dalla coda, anche se rifiutata.
    richieste.pop();
    return riuscito ? EsitoRichiesta::ACCETTATA : EsitoRichiesta::RIFIUTATA;
}
