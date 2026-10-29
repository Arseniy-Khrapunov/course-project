// Лабораторная работа № 3. Умные указатели.
#include "../include/Crew.hpp"
#include "../include/Module.hpp"
#include "../include/Station.hpp"

#include <iostream>
#include <memory>
#include <windows.h>

using namespace station;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "===== ЛР 3. Умные указатели =====\n\n";

    // 1. unique_ptr: объект уничтожается при выходе из блока без delete
    std::cout << "--- 1. unique_ptr: выход из блока ---\n";
    {
        std::unique_ptr<Station> station = std::make_unique<Station>("Станция-A");
        station->AddModule("Жилой отсек", Module::Type::eLiving, 100);
        station->Report();
    } // Здесь объект уничтожается автоматически

    // 2. unique_ptr: передача владения через std::move
    std::cout << "\n--- 2. unique_ptr: передача владения ---\n";
    std::unique_ptr<Station> original = std::make_unique<Station>("Станция-B");
    std::cout << "До move: original " << (original ? "не пуст" : "пуст") << "\n";
    std::unique_ptr<Station> moved = std::move(original);
    std::cout << "После move: original " << (original ? "не пуст" : "пуст") << "\n";

    // 3. shared_ptr: счетчик владельцев
    std::cout << "\n--- 3. shared_ptr: счетчик владельцев ---\n";
    auto engineer = std::make_shared<Crew>("Иванов", Crew::Role::eEngineer);
    std::cout << "use_count (изначально): " << engineer.use_count() << "\n";
    {
        auto engineer2 = engineer; // копия
        std::cout << "use_count (в блоке): " << engineer.use_count() << "\n";
    }
    std::cout << "use_count (после блока): " << engineer.use_count() << "\n";

    // 4. weak_ptr: наблюдение
    std::cout << "\n--- 4. weak_ptr: наблюдение ---\n";
    std::weak_ptr<Crew> watcher = engineer;

    moved->AddCrew(engineer); // Передаем shared_ptr в станцию
    moved->Report();

    // Уничтожаем последнего владельца
    engineer.reset();
    std::cout << "\nПосле reset() (уничтожен последний владелец):\n";
    std::cout << "Объект жив? " << (watcher.lock() ? "да" : "нет") << "\n";
    moved->Report(); // Программа должна корректно обработать мертвый weak_ptr

    std::cout << "\n===== Конец демонстрации =====\n";
    return 0;
}
