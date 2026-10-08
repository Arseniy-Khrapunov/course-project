// Лабораторная работа № 2. Классы, агрегация и композиция.
// Курсовой проект: Симулятор управления космической станцией.
// Храпунов А. А., группа ПИ-53.

#include "../include/Crew.hpp"
#include "../include/Module.hpp"
#include "../include/Station.hpp"
#include <windows.h>
#include <iostream>

using namespace station;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::cout << "===== Демонстрация композиции и агрегации =====\n\n";

    // Агрегация: экипаж создаётся ВНЕ станции
    Crew engineer("Иванов", Crew::Role::eEngineer);
    Crew doctor("Петрова", Crew::Role::eDoctor);

    // Композиция: станция создаётся, модули — её части
    {
        Station station("МКС-1");
        station.AddModule("Жилой отсек", Module::Type::eLiving, 100);
        station.AddModule("Реактор",     Module::Type::eReactor, 100);

        // Агрегация: передаём указатели на уже созданные объекты
        station.AddCrew(&engineer);
        station.AddCrew(&doctor);

        station.Report();

        // Динамическая инициализация объекта
        std::cout << "\n--- Динамическая инициализация объекта ---\n";
        Station* dynamicStation = new Station("Динамическая станция");
        dynamicStation->AddModule("Лаборатория", Module::Type::eLab, 100);
        dynamicStation->Report();
        delete dynamicStation;

        // Проверка правила: мёртвого нельзя лечить
        std::cout << "\n--- Проверка правила: мёртвого нельзя лечить ---\n";
        engineer.Wound();
        doctor.Heal();

        // Проверка правила: прочность не может быть отрицательной
        std::cout << "\n--- Проверка правила: прочность модуля ---\n";
        Module testModule("Тестовый модуль", Module::Type::eLiving, 50);
        testModule.Damage(30);
        testModule.Damage(30);

        // Работа по ссылке и указателю
        std::cout << "\n--- Работа по ссылке и указателю ---\n";
        Module& refModule = testModule;
        Module* ptrModule = &testModule;
        std::cout << "По ссылке: " << refModule.GetName() << "\n";
        std::cout << "По указателю: " << ptrModule->GetName() << "\n";

        // Динамический массив объектов
        std::cout << "\n--- Динамический массив модулей ---\n";
        Module* array = new Module[2]
        {
            Module("Модуль-A", Module::Type::eLiving, 100),
            Module("Модуль-B", Module::Type::eReactor, 100)
        };
        for (int i = 0; i < 2; ++i)
        {
            std::cout << "Массив[" << i << "]: " << array[i].GetName() << "\n";
        }
        delete[] array;

    } // <-- Здесь станция уничтожается, модули уничтожаются вместе с ней

    // Агрегация: экипаж остался жив после уничтожения станции
    std::cout << "\n--- После уничтожения станции ---\n";
    std::cout << "Экипаж продолжает существовать:\n";
    std::cout << "  " << engineer.GetName() << " (жив? "
              << (engineer.GetState() != Crew::State::eDead ? "да" : "нет") << ")\n";
    std::cout << "  " << doctor.GetName() << " (жив? "
              << (doctor.GetState() != Crew::State::eDead ? "да" : "нет") << ")\n";

    std::cout << "\n===== Конец демонстрации =====\n";
    return 0;
}
