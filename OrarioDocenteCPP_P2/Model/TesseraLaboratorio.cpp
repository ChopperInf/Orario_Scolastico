#include "TesseraLaboratorio.h"
#include "../DebugP2.h"
TesseraLaboratorio::TesseraLaboratorio(
    std::string materia, std::string classe, std::string aula,
    std::string tipoLaboratorio, std::string docenteITP,
    DotazioneLabInformatica* dotazione)
    : Tessera(materia, classe, aula), tipoLaboratorio(tipoLaboratorio),
      docenteITP(docenteITP), dotazione(dotazione) {
    LOG_CTOR("TesseraLaboratorio this=" << this << " tipo=" << tipoLaboratorio);
}
TesseraLaboratorio::~TesseraLaboratorio() {
    LOG_DTOR("TesseraLaboratorio this=" << this << " tipo=" << tipoLaboratorio);
    delete dotazione;
}
std::string TesseraLaboratorio::GetTipoLaboratorio() { return tipoLaboratorio; }
std::string TesseraLaboratorio::GetDocenteITP() { return docenteITP; }
DotazioneLabInformatica* TesseraLaboratorio::GetDotazione() { return dotazione; }
std::string TesseraLaboratorio::GetDescrizione() {
    std::string testo = "LABORATORIO - " + Tessera::GetDescrizione() +
        " - tipo: " + tipoLaboratorio + " - docente ITP: " + docenteITP;
    if (dotazione != nullptr) {
        testo += " - postazioni: " + std::to_string(dotazione->GetNumeroPostazioni());
        testo += dotazione->GetPresenzaLIM() ? " - LIM presente" : " - LIM assente";
    }
    return testo;
}
