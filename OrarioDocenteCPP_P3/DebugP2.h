#pragma once
// Interruttore didattico: commentare la riga seguente per spegnere i messaggi.
// Il progetto normale resta sempre silenzioso: non definisce PROGETTO_DEBUG_P2.
#define ABILITA_DEBUG_P2

#if defined(PROGETTO_DEBUG_P2) && defined(ABILITA_DEBUG_P2)
#include <iostream>
#define LOG_CTOR(msg) do { std::cerr << "[DEBUG] (+) COSTRUTTORE: " << msg << std::endl; } while (false)
#define LOG_DTOR(msg) do { std::cerr << "[DEBUG] (-) DISTRUTTORE: " << msg << std::endl; } while (false)
#else
#define LOG_CTOR(msg) ((void)0)
#define LOG_DTOR(msg) ((void)0)
#endif
