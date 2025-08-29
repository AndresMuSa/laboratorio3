#include <iostream>
#include "SteamFighter.h"

SteamFighter::SteamFighter(std::string n, int def, Ataque a1, Ataque a2, Ataque a3, Ataque a4)
    : nombre(n), defensa(def) {
    ataques[0] = a1;
    ataques[1] = a2;
    ataques[2] = a3;
    ataques[3] = a4;
}

void SteamFighter::atacar(SteamFighter& oponente, int numAtaque) {
    int danoReal = ataques[numAtaque].danoBase - oponente.defensa;
    if (danoReal < 0) danoReal = 0;

    oponente.vida -= danoReal;
    std::cout << nombre << " ha usado " << ataques[numAtaque].nombre << " y ha infligido " << danoReal << " de dano a " << oponente.nombre << ".\n";
}

bool SteamFighter::estaVivo() const {
    return vida > 0;
}

void SteamFighter::mostrarAtaques() const {
    for (size_t i = 0; i < ataques.size(); ++i) {
        std::cout << i + 1 << ". " << ataques[i].nombre
                  << " (Danio: " << ataques[i].danoBase << ")\n";
    }
}