#ifndef MAPA_H
#define MAPA_H

#include <memory>
#include <fstream>
#include <sstream>
#include "Bunka.h"
#include <iomanip>

class Mapa {
private:
    int riadky;
    int stlpce;
    std::unique_ptr<std::unique_ptr<Bunka[]>[]> poleBuniek;
    bool jeBezvetrie;
    int smerVetru;

public:
    Mapa(int a, int b);
    bool getBezvetrie();
    void nastavPociatocnyOhen(int x, int y);
    int random(int min, int max);
    void vypis();
    bool horiNad(int i, int j);
    bool horiPod(int i, int j);
    bool horiVpravo(int i, int j);
    bool horiVlavo(int i, int j);
    bool jeVOkoliVoda(int i, int j);
    bool jeVOkoliLes(int i, int j);
    void spawniVietor();
    void krok();
    void setSmerVetru(int strana);
    void ulozDoSuboru();
    void nacitajZoSuboru();
    void generujNahodne();
    void generujRucne();
    std::string getAktualnySvet();
    std::string vypisSmerVetru(int smer);
    int getSmerVetru() {return smerVetru;}

    void setVygenerovanie();
};

#endif // MAPA_H
