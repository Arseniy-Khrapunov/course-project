#include "../include/Station.h"
#include <iostream>

Station::Station() {
    turn = 0;
    gameOver = false;
}

void Station::run() {
    while (!gameOver) {
        std::cout << "=== Ход " << turn << " ===\n";
        std::cout << "Тут будет отчёт о станции и ввод команд.\n";

        turn++;
        if (turn >= 3) {
            std::cout << "Заглушка: игра закончена.\n";
            gameOver = true;
        }
    }
}
