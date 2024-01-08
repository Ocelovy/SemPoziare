#include "Mapa.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>

Mapa::Mapa(int a, int b) {
    riadky = a;
    stlpce = b;

    poleBuniek = std::make_unique<std::unique_ptr<Bunka[]>[]>(riadky);
    for (int i = 0; i < a; ++i) {
        poleBuniek[i] = std::make_unique<Bunka[]>(stlpce);
    }

    int cislo;
    std::cout << "Ako chces generovat pravdepodobnost ? 1 = nahodne, 2 = rucne\n";
    std::cin >> cislo;

    if (cislo == 1) {
        this->generujNahodne();
    } else {
        this->generujRucne();
    }

    this->vypis();
}



void Mapa::generujNahodne() {
    for (int i = 0; i < riadky; ++i) {
        for (int j = 0; j < stlpce; ++j) {
            int vygenerovanaHodnota = random(1, 4);
            poleBuniek[i][j].setTyp(vygenerovanaHodnota);
        }
    }
}

void Mapa::generujRucne() {
    int hodnota;
    for (int i = 0; i < riadky; ++i) {
        for (int j = 0; j < stlpce; ++j) {
            int vygenerovanaHodnota = random(1, 4);
            std::cout << "Zadaj hodnotu pre bunku " << i << " " << j << "! 1 = LES, 2 = LUKA, 3 = SKALY, 4 = VODA, 5 = OHEN\n";
            std::cin >> hodnota;
            poleBuniek[i][j].setTyp(hodnota);
        }
    }
}


bool Mapa::getBezvetrie() {
    return jeBezvetrie;
}

void Mapa::nastavPociatocnyOhen(int x, int y) {
    poleBuniek[x][y].zapalSa();
    vypis();
    std::cout << "Zadaj vstup ! (1 = pokracovat, 2 = zadat ohen, 3 = ukoncit, 4 = ulozit do suboru, 5 = nacitaj zo suboru)" << std::endl;
}

int Mapa::random(int min, int max) {
    thread_local auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    thread_local static std::mt19937 prng(seed);
    thread_local static bool init = true;
    if (init) {
        prng.discard(10000);
        init = false;
    }

    return std::uniform_int_distribution<int>(min, max)(prng);
}

void Mapa::vypis() {
    std::cout << std::endl;
    for (int i = 0; i < riadky; ++i) {
        for (int j = 0; j < stlpce; ++j) {
            std::cout << std::setw(4) << poleBuniek[i][j].getZnak();

        }
        std::cout << std::endl;
    }
}

bool Mapa::horiNad(int i, int j) {
    if (i - 1 >= 0 && poleBuniek[i - 1][j].getHori()) {
        return true;
    }
    return false;
}

bool Mapa::horiPod(int i, int j) {
    if (i + 1 < riadky && poleBuniek[i + 1][j].getHori()) {
        return true;
    }
    return false;
}

bool Mapa::horiVpravo(int i, int j) {
    if (j + 1 < stlpce && poleBuniek[i][j + 1].getHori()) {
        return true;
    }
    return false;
}

bool Mapa::horiVlavo(int i, int j) {
    if (j - 1 >= 0 && poleBuniek[i][j - 1].getHori()) {
        return true;
    }
    return false;
}

bool Mapa::jeVOkoliVoda(int i, int j) {
    if (i + 1 < riadky && poleBuniek[i + 1][j].getTyp() == BiotopTyp::VODA ||
        i - 1 >= 0 && poleBuniek[i - 1][j].getTyp() == BiotopTyp::VODA ||
        j - 1 >= 0 && poleBuniek[i][j - 1].getTyp() == BiotopTyp::VODA ||
        j + 1 < stlpce && poleBuniek[i][j + 1].getTyp() == BiotopTyp::VODA) {
        return true;
    }
    return false;
}

bool Mapa::jeVOkoliLes(int i, int j) {
    if (i + 1 < riadky && poleBuniek[i + 1][j].getTyp() == BiotopTyp::LES ||
        i - 1 >= 0 && poleBuniek[i - 1][j].getTyp() == BiotopTyp::LES ||
        j - 1 >= 0 && poleBuniek[i][j - 1].getTyp() == BiotopTyp::LES ||
        j + 1 < stlpce && poleBuniek[i][j + 1].getTyp() == BiotopTyp::LES) {
        return true;
    }
    return false;
}

void Mapa::spawniVietor() {
    jeBezvetrie = false;
    setSmerVetru(random(1, 4));
}

void Mapa::krok() {
    //std::cout << vypisSmerVetru(smerVetru) << std::endl;
    for (int i = 0; i < riadky; ++i) {
        for (int j = 0; j < stlpce; ++j) {
            if (poleBuniek[i][j].getRozhorievaSa()) {
                poleBuniek[i][j].rozhorSa();
            }
        }
    }

    for (int i = 0; i < riadky; ++i) {
        for (int j = 0; j < stlpce; ++j) {
            if (jeBezvetrie) {
                if (horiPod(i, j) || horiNad(i, j) || horiVlavo(i, j) || horiVpravo(i, j)) {
                    if (random(0, 100) < 20)
                        poleBuniek[i][j].zapalSa();
                }
            } else {
                if (random(0, 100) < 90) {
                    if (horiPod(i, j) && smerVetru == 1) { // fuka na sever
                        poleBuniek[i][j].zapalSa();
                    } else if (horiNad(i, j) && smerVetru == 2) { // fuka na juh
                        poleBuniek[i][j].zapalSa();
                    } else if (horiVlavo(i, j) && smerVetru == 3) { // fuka na vychod
                        poleBuniek[i][j].zapalSa();
                    } else if (horiVpravo(i, j) && smerVetru == 4) { // fuka na zapad
                        poleBuniek[i][j].zapalSa();
                    }
                }
                if (random(0, 100) < 2) {
                    if (horiNad(i, j) && smerVetru == 1) { // fuka na sever
                        poleBuniek[i][j].zapalSa();
                    } else if (horiPod(i, j) && smerVetru == 2) { // fuka na juh
                        poleBuniek[i][j].zapalSa();
                    } else if (horiVpravo(i, j) && smerVetru == 3) { // fuka na vychod
                        poleBuniek[i][j].zapalSa();
                    } else if (horiVlavo(i, j) && smerVetru == 4) { // fuka na zapad
                        poleBuniek[i][j].zapalSa();
                    }
                }
            }

            if (poleBuniek[i][j].getHori() && jeVOkoliVoda(i, j)) {
                if (random(0, 100) < 10) {
                    poleBuniek[i][j].setTyp(2);
                }
            }

            if (jeVOkoliLes(i, j) && poleBuniek[i][j].getTyp() == BiotopTyp::LUKA) {
                if (random(0, 100) < 2) {
                    poleBuniek[i][j].setTyp(1);
                }
            }
        }
    }
    this->vypis();
}

void Mapa::setSmerVetru(int strana) {
    if (strana > 4) {
        jeBezvetrie = true;
        smerVetru = 5;
    } else {
        smerVetru = strana;
        jeBezvetrie = false;
    }
}


std::string Mapa::vypisSmerVetru(int smer) {
    std::string vypis = "";
    switch (smer) {
        case 1:
            return vypis += "Fuka na sever";
        case 2:
            return vypis += "Fuka na juh";
        case 3:
            return vypis += "Fuka na vychod";
        case 4:
            return vypis += "Fuka na zapad";
        case 5:
            return vypis += "Je bezvetrie";
    }
}

void Mapa::ulozDoSuboru() {
    std::ofstream suborNaZapis("C:\\Users\\tomas\\CLionProjects\\semka\\aktualnySvet.txt");

    if (!suborNaZapis.is_open()) {
        std::cerr << "Nepodarilo sa otvorit suborNaZapis na zapis." << std::endl;
        return;
    }

    for (int i = 0; i < riadky; ++i) {
        for (int j = 0; j < stlpce; ++j) {
            suborNaZapis << poleBuniek[i][j].getZnak();
        }
        suborNaZapis << "\n";
    }

    suborNaZapis.close();
    std::cout << "Aktualny svet bol uspesne ulozeny do suboru.\n";
}

void Mapa::nacitajZoSuboru() {
    std::ifstream suborNacitanie("C:\\Users\\tomas\\CLionProjects\\semka\\aktualnySvet.txt");

    if (!suborNacitanie.is_open()) {
        std::cerr << "Nepodarilo sa otvorit subor na citanie." << std::endl;
        return;
    }

    for (int i = 0; i < riadky; ++i) {
        for (int j = 0; j < stlpce; ++j) {
            int cislo;
            char znak;
            suborNacitanie >> znak;

            switch (znak) {
                case '|':
                    cislo = 1;
                    break;
                case '_':
                    cislo = 2;
                    break;
                case 'O':
                    cislo = 3;
                    break;
                case '~':
                    cislo = 4;
                    break;
                case 'V':
                    cislo = 5;
                    break;
            }
            poleBuniek[i][j].setTyp(cislo);
        }
        suborNacitanie.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    suborNacitanie.close();
    std::cout << "Data boli uspesne nacitane zo suboru.\n";
}

std::string Mapa::getAktualnySvet() {
    std::string result = "\n";

    for (int i = 0; i < riadky; ++i) {
        for (int j = 0; j < stlpce; ++j) {
            result += poleBuniek[i][j].getZnak();
        }
        result += "\n";
    }
    return result;
}

