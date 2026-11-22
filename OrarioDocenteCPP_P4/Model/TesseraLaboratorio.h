#pragma once
#include "Tessera.h"
#include "DotazioneLabInformatica.h"
class TesseraLaboratorio : public Tessera {
private:
    std::string tipoLaboratorio;
    std::string docenteITP;
    DotazioneLabInformatica* dotazione;
public:
    // La tessera acquisisce la proprieta' del puntatore ricevuto, se non nullo.
    TesseraLaboratorio(std::string materia, std::string classe, std::string aula,
                       std::string tipoLaboratorio, std::string docenteITP,
                       DotazioneLabInformatica* dotazione);
    ~TesseraLaboratorio() override;
    TesseraLaboratorio(const TesseraLaboratorio&) = delete;
    TesseraLaboratorio& operator=(const TesseraLaboratorio&) = delete;
    std::string GetTipoLaboratorio();
    std::string GetDocenteITP();
    // Puntatore non proprietario: non chiamare delete sul risultato.
    DotazioneLabInformatica* GetDotazione();
    std::string GetDescrizione() override;
};
