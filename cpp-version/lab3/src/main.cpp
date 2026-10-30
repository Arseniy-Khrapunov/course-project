#include "../include/Crew.hpp"
#include "../include/Module.hpp"
#include "../include/Station.hpp"

#include <iostream>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    using station::Crew;
    using station::Module;
    using station::Station;

    std::cout << "===== ЛР 3. Умные указатели =====\n\n";

    // 1. unique_ptr: объект уничтожается при выходе из блока без delete
    std::cout << "--- 1. unique_ptr: выход из блока ---\n";
    {
        std::unique_ptr<Station> temp = std::make_unique<Station>("Станция-A");
        temp->AddModule("Жилой отсек", Module::Type::eLiving, 100);
        temp->AddModule("Реактор", Module::Type::eReactor, 100);
        temp->AddModule("Лаборатория", Module::Type::eLab, 100); // массив растёт
        temp->Report();
    } // здесь станция и её модули уничтожены автоматически
    std::cout << "(блок закончился)\n";

    // 1а. Массив из ЛР 2 (был new Module[2] / delete[])
    std::cout << "\n--- 1а. Массив умных указателей ---\n";
    {
        std::unique_ptr<Module> shelf[2];
        shelf[0] = std::make_unique<Module>("Модуль-A", Module::Type::eLiving, 100);
        shelf[1] = std::make_unique<Module>("Модуль-B", Module::Type::eReactor, 100);
    } // оба модуля уничтожены без delete[]

    // 2. unique_ptr: передача владения через std::move
    std::cout << "\n--- 2. unique_ptr: передача владения ---\n";
    std::unique_ptr<Station> original = std::make_unique<Station>("Станция-B");
    std::cout << "До move: original " << (original ? "не пуст" : "пуст") << "\n";
    std::unique_ptr<Station> moved = std::move(original);
    std::cout << "После move: original " << (original ? "не пуст" : "пуст") << "\n";

    // 3. shared_ptr: счётчик владельцев
    std::cout << "\n--- 3. shared_ptr: счётчик владельцев ---\n";
    auto engineer = std::make_shared<Crew>("Иванов", Crew::Role::eEngineer);
    std::cout << "use_count (изначально): " << engineer.use_count() << "\n";
    {
        auto engineer2 = engineer; // копия указателя — второй владелец
        std::cout << "use_count (в блоке): " << engineer.use_count() << "\n";
    }
    std::cout << "use_count (после блока): " << engineer.use_count() << "\n";

    // 4. weak_ptr: наблюдение
    std::cout << "\n--- 4. weak_ptr: наблюдение ---\n";
    std::weak_ptr<Crew> watcher = engineer;
    moved->AddCrew(engineer);
    std::cout << "use_count после AddCrew: " << engineer.use_count()
              << " (станция только наблюдает)\n";
    moved->AddCrew(nullptr); // проверка правила
    moved->Report();

    if (auto alive = watcher.lock())
    {
        std::cout << "lock() пока жив: " << alive->GetName()
                  << ", use_count = " << alive.use_count() << "\n";
    }

    engineer.reset(); // ушёл последний владелец
    std::cout << "\nПосле reset() (уничтожен последний владелец):\n";
    if (auto alive = watcher.lock())
    {
        std::cout << "Объект жив: " << alive->GetName() << "\n";
    }
    else
    {
        std::cout << "lock() вернул пустой указатель — объект уничтожен\n";
    }
    moved->Report();

    std::cout << "\n===== Конец демонстрации =====\n";
    return 0;
}
