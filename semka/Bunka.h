#ifndef BUNKA_H
#define BUNKA_H

#include <string>

enum class BiotopTyp {
    LES,
    LUKA,
    SKALY,
    VODA,
    OHEN
};

class Bunka {
private:
    bool jeHorlava;
    bool hori;
    bool rozhorievaSa;
    BiotopTyp typ;
    std::string znak;

public:
    Bunka();
    void setTyp(int cislo);
    bool getHori();
    bool getRozhorievaSa();
    BiotopTyp getTyp();
    void zapalSa();
    void rozhorSa();
    void uhasSa();
    std::string getZnak();
};

#endif // BUNKA_H