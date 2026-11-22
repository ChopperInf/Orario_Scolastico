#pragma once
#include "Vincolo.h"

class VincoloSenzaBuchi : public Vincolo {
public:
    VincoloSenzaBuchi();
    ~VincoloSenzaBuchi() override;
    bool Verifica(Orario& orario) override;
    std::string GetMessaggio() override { return "sono presenti buchi nell'orario"; }
};
