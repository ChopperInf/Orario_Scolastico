#pragma once
#include <string>
#include <vector>
class DotazioneLabInformatica {
private:
    std::vector<std::string> postazioni;
    bool presenzaLIM;
public:
    DotazioneLabInformatica(std::vector<std::string> postazioni, bool presenzaLIM);
    ~DotazioneLabInformatica();
    int GetNumeroPostazioni();
    std::string GetDescrizionePostazione(int indice);
    bool GetPresenzaLIM();
};
