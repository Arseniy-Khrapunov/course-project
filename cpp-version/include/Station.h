#ifndef STATION_H
#define STATION_H

// Главный класс станции.
// Пока тут только заготовка — потом добавлю модули, экипаж и ресурсы.
class Station {
public:
    Station();
    void run();

private:
    int turn;        // номер хода
    bool gameOver;   // закончилась ли игра
};

#endif
