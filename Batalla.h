#ifndef BATALLA_H
#define BATALLA_H

#include "SteamFighter.h"

class Batalla {
public:
    Batalla(SteamFighter& luchador1, SteamFighter& luchador2);
    void iniciarBatalla();

private:
    SteamFighter& luchador1;
    SteamFighter& luchador2;

    void mostrarEstado() const;
    void menuTurno(SteamFighter& atacante, SteamFighter& defensor);
};

#endif