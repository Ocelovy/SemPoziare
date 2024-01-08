#include <random>
#include "Simulacia.h"

using namespace std;

int main(int argc, char* argv[]) {

    Simulacia simulacia(atoi(argv[1]), atoi(argv[2]));

    std::thread t1(&Simulacia::simuluj, &simulacia);

    // Start the input thread
    std::thread t2(&Simulacia::dajVstup, &simulacia);

    // Wait for the input thread to finish
    t2.join();

    // Notify the simulation thread that input is received and wait for it to finish
    std::unique_lock<std::mutex> lock(simulacia.getMutex());
    simulacia.setInputRecived(true);
    lock.unlock();
    simulacia.getConditionVariable().notify_one();
    t1.join();

    return 0;

}