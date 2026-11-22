#pragma once
#include "../Model/Orario.h"
#include <string>
#include "../DebugP2.h"

// Interfaccia comune a tutti i controlli dell'orario.
class Vincolo {
public:
    Vincolo() { LOG_CTOR("Vincolo this=" << this); }
    virtual bool Verifica(Orario& orario) = 0;
    virtual std::string GetMessaggio() = 0;
    virtual ~Vincolo() { LOG_DTOR("Vincolo this=" << this); }
};
