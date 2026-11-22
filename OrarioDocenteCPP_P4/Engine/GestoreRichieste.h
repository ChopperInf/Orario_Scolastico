#pragma once
#include <queue>
#include <string>
#include "RichiestaScambio.h"
#include "MotoreScambi.h"

enum class EsitoRichiesta { CODA_VUOTA, ACCETTATA, RIFIUTATA };

// La coda conserva richieste; MotoreScambi conserva la cronologia delle modifiche.
class GestoreRichieste {
private:
    std::queue<RichiestaScambio> richieste;
public:
    void Accoda(const RichiestaScambio& richiesta);
    bool Vuota() const;
    std::size_t NumeroRichieste() const;
    EsitoRichiesta ElaboraPrima(MotoreScambi& motore, Orario& orario,
                               std::string& messaggio);
};
