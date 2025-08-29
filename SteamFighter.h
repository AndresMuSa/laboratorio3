#ifndef STEAMFIGHTER_H
#define STEAMFIGHTER_H

#include <string>
#include <array>

class Ataque {
public:
    std::string nombre;
    int danoBase;
    int costoStamina; // Se mantiene para compatibilidad con la estructura, pero su valor será 0
    std::string efecto;
};

class SteamFighter {
public:
    std::string nombre;
    int vida = 100;
    int defensa = 10;
    std::array<Ataque, 4> ataques;

    SteamFighter(std::string n, int def, Ataque a1, Ataque a2, Ataque a3, Ataque a4);

    void atacar(SteamFighter& oponente, int numAtaque);
    bool estaVivo() const;
    void mostrarAtaques() const;
};

#endif