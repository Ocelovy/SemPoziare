#include <iostream>
#include "Bunka.h"

Bunka::Bunka() {
    jeHorlava = false;
    hori = false;
    rozhorievaSa = false;
    typ = BiotopTyp::LES;
    znak = '|';
}

void Bunka::setTyp(int cislo) {
    switch (cislo) {
        case 1:
            typ = BiotopTyp::LES;
            jeHorlava = true;
            znak = '|';
            break;
        case 2:
            typ = BiotopTyp::LUKA;
            jeHorlava = true;
            znak = '_';
            break;
        case 3:
            typ = BiotopTyp::SKALY;
            znak = 'O';
            break;
        case 4:
            typ = BiotopTyp::VODA;
            znak = '~';
            break;
        case 5:
            typ = BiotopTyp::OHEN;
            znak = 'V';
            break;
        default:
            std::cout << "Zadal si nespravnu hodnotu, nastavujem na SKALY.\n";
            typ = BiotopTyp::SKALY;
            znak = 'O';
            break;
    }
}


bool Bunka::getHori() {
    return hori;
}

bool Bunka::getRozhorievaSa() {
    return rozhorievaSa;
}

BiotopTyp Bunka::getTyp() {
    return typ;
}

void Bunka::zapalSa() {
    if (jeHorlava) {
        rozhorievaSa = true;
        znak = 'V';
    }
}

void Bunka::rozhorSa() {
    jeHorlava = true;
    rozhorievaSa = false;
    hori = true;
}

void Bunka::uhasSa() {
    hori = false;
    jeHorlava = false;
    znak = '#';
}

std::string Bunka::getZnak() {
    return znak;
}
