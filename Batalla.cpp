#include <iostream>
#include <limits>
#include "Batalla.h"
#include "SteamFighter.h"

Batalla::Batalla(SteamFighter& l1, SteamFighter& l2) : luchador1(l1), luchador2(l2) {}

void Batalla::mostrarEstado() const {
    std::cout << "\n--- Estado de la batalla ---\n";
    std::cout << luchador1.nombre << ": " << luchador1.vida << " HP\n";
    std::cout << luchador2.nombre << ": " << luchador2.vida << " HP\n";
    std::cout << "--------------------------\n";
}

void Batalla::menuTurno(SteamFighter& atacante, SteamFighter& defensor) {
    std::cout << "\n--- Turno de " << atacante.nombre << " ---\n";
    
    atacante.mostrarAtaques();
    std::cout << "Elige un ataque (1-4): ";
    int numAtaque;
    std::cin >> numAtaque;

    while (std::cin.fail() || numAtaque < 1 || numAtaque > 4) {
        std::cout << "Error: Ataque invalido. Ingresa un numero entre 1 y 4: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> numAtaque;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    atacante.atacar(defensor, numAtaque - 1);
}

void Batalla::iniciarBatalla() {
    std::cout << "\n--- ¡La batalla comienza! " << luchador1.nombre << " vs " << luchador2.nombre << " ---\n";
    
    luchador1.vida = 100;
    luchador2.vida = 100;

    int turno = 1;
    while (luchador1.estaVivo() && luchador2.estaVivo()) {
        mostrarEstado();
        if (turno % 2 != 0) {
            menuTurno(luchador1, luchador2);
        } else {
            menuTurno(luchador2, luchador1);
        }
        turno++;
    }

    mostrarEstado();
    if (luchador1.estaVivo()) {
        std::cout << "\n¡" << luchador1.nombre << " ha ganado la batalla!\n";
    } else {
        std::cout << "\n¡" << luchador2.nombre << " ha ganado la batalla!\n";
    }
}