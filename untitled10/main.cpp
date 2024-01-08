#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

enum Biotop { LES, LUKA, SKALY, VODA, HORENIE, ZHORELA };

enum WindDirection { NONE, FROM_BURNING_CELL, TOWARDS_BURNING_CELL };

class World {
public:
    World(int rows, int cols) : rows(rows), cols(cols), windDirection(NONE) {
        map.resize(rows, std::vector<Biotop>(cols, VODA));
    }

    void generateRandomWorld(double probabilityLes, double probabilityLuka, double probabilitySkaly, double probabilityVoda) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double randNum = static_cast<double>(rand()) / RAND_MAX;

                if (randNum < probabilityLes) map[i][j] = LES;
                else if (randNum < probabilityLes + probabilityLuka) map[i][j] = LUKA;
                else if (randNum < probabilityLes + probabilityLuka + probabilitySkaly) map[i][j] = SKALY;
                else map[i][j] = VODA;
            }
        }
    }

    void printWorld() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                char symbol = getBiotopSymbol(map[i][j]);
                std::cout << symbol << ' ';
            }
            std::cout << std::endl;
        }
    }

    void setOnFire(int row, int col) {
        if (isValidCell(row, col)) {
            map[row][col] = HORENIE;
        }
    }

    void simulateFireSpread() {
        std::vector<std::vector<Biotop>> newMap = map;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (map[i][j] == HORENIE) {
                    spreadFire(i, j, newMap);
                }
            }
        }

        map = newMap;
    }

    void setWindDirection(WindDirection direction) {
        windDirection = direction;
    }

private:
    std::vector<std::vector<Biotop>> map;
    int rows, cols;
    WindDirection windDirection;

    char getBiotopSymbol(Biotop biotop) const {
        switch (biotop) {
            case LES: return 'L';
            case LUKA: return 'U';
            case SKALY: return 'S';
            case VODA: return 'W';
            case HORENIE: return 'F';
            case ZHORELA: return 'B';
            default: return ' ';
        }
    }

    bool isValidCell(int row, int col) const {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }

    void spreadFire(int row, int col, std::vector<std::vector<Biotop>>& newMap) {
        std::pair<int, int> neighbors[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        for (const auto& neighbor : neighbors) {
            int newRow = row + neighbor.first;
            int newCol = col + neighbor.second;

            if (isValidCell(newRow, newCol) && (map[newRow][newCol] == LES || map[newRow][newCol] == LUKA)) {
                double probability = 0.0;

                if (windDirection == NONE) {
                    probability = 0.2; // bezvetrie
                } else if (windDirection == FROM_BURNING_CELL) {
                    probability = 0.9; // vietor od horiacej bunky k tejto bunke
                } else if (windDirection == TOWARDS_BURNING_CELL) {
                    probability = 0.02; // vietor od tejto bunky k horiacej
                }

                double randNum = static_cast<double>(rand()) / RAND_MAX;

                if (randNum < probability) {
                    newMap[newRow][newCol] = HORENIE;
                }
            }
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Inicializácia sveta
    int rows = 10;
    int cols = 10;
    World world(rows, cols);

    // Generovanie sveta s určenými pravdepodobnosťami biotopov
    world.generateRandomWorld(0.2, 0.3, 0.1, 0.4);

    // Vypísanie sveta
    std::cout << "Initial World:" << std::endl;
    world.printWorld();

    // Nastavenie niektorých buniek na požiar
    world.setOnFire(0, 0);
    world.setOnFire(1, 1);

    // Nastavenie smeru vetra
    world.setWindDirection(FROM_BURNING_CELL);

    // Simulácia šírenia požiaru
    world.simulateFireSpread();

    // Vypísanie sveta po simulácii
    std::cout << "\nWorld After Simulation:" << std::endl;
    world.printWorld();


    // Simulácia šírenia požiaru
    world.simulateFireSpread();

    // Vypísanie sveta po simulácii
    std::cout << "\nWorld After Simulation:" << std::endl;
    world.printWorld();


    // Simulácia šírenia požiaru
    world.simulateFireSpread();

    // Vypísanie sveta po simulácii
    std::cout << "\nWorld After Simulation:" << std::endl;
    world.printWorld();

    // Simulácia šírenia požiaru
    world.simulateFireSpread();

    // Vypísanie sveta po simulácii
    std::cout << "\nWorld After Simulation:" << std::endl;
    world.printWorld();

    // Simulácia šírenia požiaru
    world.simulateFireSpread();

    // Vypísanie sveta po simulácii
    std::cout << "\nWorld After Simulation:" << std::endl;
    world.printWorld();

    // Simulácia šírenia požiaru
    world.simulateFireSpread();

    // Vypísanie sveta po simulácii
    std::cout << "\nWorld After Simulation:" << std::endl;
    world.printWorld();

    return 0;
}
