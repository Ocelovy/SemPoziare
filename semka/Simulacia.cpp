#include "Simulacia.h"
#include <iostream>

Simulacia::Simulacia(int a, int b) : mapa(a, b) {
    this->pocetDni = 0;
    //MySocket* mySocket = MySocket::createConnection("frios2.fri.uniza.sk", 19120);
    //MySocket::createConnection("frios2.fri.uniza.sk", 19120);
}

Simulacia::~Simulacia() {
    //delete serverSocket;
    //serverSocket = nullptr;
}



void Simulacia::simuluj() {

    int pocetKolVetra = 0;
    std::cout << "Zadaj vstup ! (1 = pokracovat, 2 = zadat ohen, 3 = ukoncit, 4 = ulozit do suboru, 5 = nacitaj zo suboru)" << std::endl;
    mapa.setSmerVetru(5);
    while (this->vstup != 3) {
        std::unique_lock<std::mutex> lock(mtx);

        if (this->vstup == 1) {
            std::cout<<std::endl;
            std::cout<<"Pocet dni simulacie je: "<< pocetDni <<std::endl;
            std::cout<<this->mapa.vypisSmerVetru(mapa.getSmerVetru())<<std::endl;
            std::cout << "Zadaj vstup ! (1 = pokracovat, 2 = zadat ohen, 3 = ukoncit, 4 = ulozit do suboru, 5 = nacitaj zo suboru)" << std::endl;

            if (pocetKolVetra >= 2) {
                mapa.setSmerVetru(5);
                pocetKolVetra = 0;
            }

            if (mapa.getBezvetrie()) {
                if (mapa.random(0, 100) < 10) {
                    mapa.spawniVietor();
                }
            } else {
                pocetKolVetra++;
            }
            mapa.krok();
            pocetDni++;
            std::cout << "pocet kol vetra: " << pocetKolVetra << std::endl;

            if (inputReceived) {
                processingInput = true;
                cv.notify_one();
                lock.unlock();

                std::unique_lock<std::mutex> processingLock(mtx);
                cv.wait(processingLock, [this] { return !processingInput; });
            } else {
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            lock.lock();


            //this->odosliSvet(mapa.getAktualnySvet());

        }

    }
    std::cout << "Ukoncujem aplikaciu." << std::endl;
}



void Simulacia::dajVstup() {
    while(this->vstup != 3) {
        // Wait for user input
        std::string input;
        std::getline(std::cin, input);

        if (input == "1") {
            vstup = 1;
        } else if (input == "2") {
            std::unique_lock<std::mutex> lock(mtx);
            nastavOhen();
            lock.unlock();
            vstup = 2;
            cv.notify_one();

        } else if (input == "3") {
            vstup = 3;
        } else if (input == "4") {
            std::unique_lock<std::mutex> lock(mtx);
            mapa.ulozDoSuboru();
            processingInput = false;
            vstup = 4;
            lock.unlock();
        } else if (input == "5") {
            std::unique_lock<std::mutex> lock(mtx);
            mapa.nacitajZoSuboru();
            processingInput = false;
            vstup = 5;
            lock.unlock();
        }

        std::unique_lock<std::mutex> lock(mtx);
        inputReceived = true;
        cv.notify_one();
        lock.unlock();


        std::unique_lock<std::mutex> processingLock(mtx);
        cv.wait(processingLock, [this] { return !processingInput; });

        //if (input == "2" || input == "4" || input == "5") {
         //   std::this_thread::sleep_for(std::chrono::milliseconds(5000));
       // }

        inputReceived = false;
    }
}



void Simulacia::nastavOhen() {

    std::cout << "Zadaj pociatocny ohen!" << std::endl;
    int x, y;
    std::cin >> x;
    std::cin >> y;
    mapa.nastavPociatocnyOhen(x, y);
    processingInput = false;

}

void Simulacia::setInputRecived(boolean vstup) {
    this->inputReceived = vstup;
}

void Simulacia::odosliSvet(const std::string& retazec) {
    //this->serverSocket->sendData(retazec);
}


