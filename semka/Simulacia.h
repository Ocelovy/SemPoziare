#ifndef SIMULACIA_H
#define SIMULACIA_H

#include "Mapa.h"
#include "MySocket.h"
#include <mutex>
#include <condition_variable>
#include <thread>

class Simulacia {
private:
    int pocetDni;
    Mapa mapa;
    int vstup = 0;
    std::mutex mtx;
    std::condition_variable cv;
    bool inputReceived = false;
    bool processingInput = false;

    std::thread t1;
    std::thread t2;
    //MySocket* serverSocket{};

public:
    Simulacia(int a, int b);
    ~Simulacia();
    void simuluj();
    void odosliSvet(const std::string& retazec);
    void nastavOhen();
    void dajVstup();
    std::condition_variable& getConditionVariable() { return cv; }
    std::mutex& getMutex() { return mtx; }
    void setInputRecived(boolean vstup);

};

#endif // SIMULACIA_H
