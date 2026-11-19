#include "../include/Crew.hpp"
#include "../include/LabModule.hpp"
#include "../include/LivingModule.hpp"
#include "../include/ReactorModule.hpp"
#include "../include/Station.hpp"

#include <iostream>
#include <memory>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    using station::BaseModule;
    using station::Crew;
    using station::Dock;
    using station::LabModule;
    using station::LivingModule;
    using station::ReactorModule;
    using station::Station;

    std::cout << "===== ЛР 4. Наследование =====\n";

    // 1. Конструкторы: по умолчанию и с параметрами; порядок вызовов
    std::cout << "\n--- 1. Конструкторы и порядок вызовов ---\n";
    {
        std::cout << "[создаём жилой модуль с параметрами]\n";
        LivingModule living{ "Жилой отсек", 100, std::make_shared<Dock>("A-1"), 4 };
        std::cout << "[создаём жилой модуль по умолчанию]\n";
        LivingModule empty;
        std::cout << "[выход из блока]\n";
    }

    // 2. Виртуальный деструктор: уничтожение наследника через указатель на базу
    std::cout << "\n--- 2. Виртуальный деструктор ---\n";
    {
        std::unique_ptr<BaseModule> pointer = std::make_unique<LabModule>(
            "Лаборатория", 90, std::make_shared<Dock>("B-2"), "биология");
        std::cout << "[pointer.reset()]\n";
        pointer.reset();
        std::cout << "[после reset]\n";
    }

    // 3. Копирование: глубокое (Dock) и поверхностное (журнал лаборатории)
    std::cout << "\n--- 3. Глубокая и поверхностная копия ---\n";
    LivingModule original{ "Жилой отсек-2", 100, std::make_shared<Dock>("A-1"), 4 };
    std::cout << "[копируем жилой модуль]\n";
    LivingModule copy = original;
    copy.RenameDock("Z-9");
    std::cout << "original: " << original.Describe() << "\n";
    std::cout << "copy:     " << copy.Describe() << "\n";
    std::cout << "Узел оригинала остался " << original.GetDockCode()
              << " — копия имеет собственный узел (глубокая копия)\n";

    LabModule lab{ "Лаборатория-2", 95, std::make_shared<Dock>("C-3"), "химия" };
    std::cout << "[копируем лабораторию]\n";
    LabModule labCopy = lab;
    labCopy.WriteLog("опыт №1");
    std::cout << "lab:      " << lab.Describe() << "\n";
    std::cout << "Журнал изменился и у оригинала; владельцев журнала: "
              << lab.GetLogUseCount() << " (поверхностная копия)\n";

    // 4. Перемещение
    std::cout << "\n--- 4. Конструктор перемещения ---\n";
    LivingModule source{ "Жилой отсек-3", 100, std::make_shared<Dock>("A-3"), 2 };
    LivingModule moved = std::move(source);
    std::cout << "moved:  " << moved.Describe() << "\n";
    std::cout << "У source после перемещения имя пустое: \""
              << source.GetName() << "\"\n";

    // 5. Массив std::unique_ptr<BaseModule>: разные наследники через указатель на базу
    std::cout << "\n--- 5. Массив unique_ptr<BaseModule> ---\n";
    std::unique_ptr<BaseModule> modules[3];
    modules[0] = std::make_unique<LivingModule>("Жилой отсек-4", 100,
                                                std::make_shared<Dock>("A-4"), 6);
    modules[1] = std::make_unique<LabModule>("Лаборатория-3", 90,
                                             std::make_shared<Dock>("B-5"), "физика");
    modules[2] = std::make_unique<ReactorModule>("Реактор-1", 100,
                                                 std::make_shared<Dock>("R-1"), 80);
    int total = 0;
    for (const auto& module : modules)
    {
        std::cout << " - " << module->Describe() << "; энергия " << module->GetPowerBalance() << "\n";
        total += module->GetPowerBalance();
    }
    std::cout << "Итого энергобаланс: " << total << "\n";
    // modules[0]->Header(); // ошибка компиляции: Header() — protected

    // 6. Клонирование через указатель на базовый класс
    std::cout << "\n--- 6. Clone() через указатель на базу ---\n";
    std::unique_ptr<BaseModule> twin = modules[1]->Clone();
    std::cout << "twin: " << twin->Describe() << "\n";

    // 7. Станция: композиция модулей разных видов
    std::cout << "\n--- 7. Станция ---\n";
    {
        Station station{ "МКС-1" };
        station.AddModule(std::move(modules[0]));
        station.AddModule(std::move(modules[1]));
        station.AddModule(modules[2]->Clone());
        station.AddModule(nullptr); // проверка правила
        auto engineer = std::make_shared<Crew>("Иванов", Crew::Role::eEngineer);
        station.AddCrew(engineer);
        station.Report();
        std::cout << "[выход из блока: станция и её модули уничтожаются]\n";
    }

    // 8. Переопределение: реактор после поломки
    std::cout << "\n--- 8. Переопределённые методы ---\n";
    std::cout << modules[2]->Describe() << "\n";
    modules[2]->Damage(100);
    std::cout << modules[2]->Describe() << "\n";

    // 9. Строки
    std::cout << "\n--- 9. Строки ---\n";
    const std::string label = std::string{ lab.GetName() } + " / " + std::string{ lab.GetSerial() };
    std::cout << "Конкатенация: " << label << "\n";
    std::cout << "Префикс (substr): " << lab.GetSerialPrefix()
              << ", номер: " << lab.GetSerialNumberPart() << "\n";
    std::cout << "NameContains(\"Лаборатория\"): " << lab.NameContains("Лаборатория") << "\n";
    std::cout << "NameContains(\"Реактор\"):     " << lab.NameContains("Реактор") << "\n";
    std::cout << "Одинаковый префикс у lab и labCopy:  " << lab.SamePrefix(labCopy) << "\n";
    std::cout << "Одинаковый префикс у lab и original: " << lab.SamePrefix(original) << "\n";
    std::cout << "Серийные номера lab и labCopy равны: "
              << (lab.GetSerial() == labCopy.GetSerial()) << "\n";
    const std::string text = "Станция МКС-1: модуль " + std::string{ lab.GetSerial() } + " в норме";
    const std::size_t pos = text.find("LAB");
    if (pos != std::string::npos)
    {
        std::cout << "find нашёл LAB на позиции " << pos << ", substr: "
                  << text.substr(pos, 7) << "\n";
    }

    // 10. this: цепочка присваиваний, самоприсваивание, передача объекта
    std::cout << "\n--- 10. this ---\n";
    LivingModule a{ "Модуль-A", 100, std::make_shared<Dock>("1"), 1 };
    LivingModule b{ "Модуль-B", 100, std::make_shared<Dock>("2"), 1 };
    LivingModule c{ "Модуль-C", 100, std::make_shared<Dock>("3"), 1 };
    std::cout << "[a = b = c]\n";
    a = b = c;
    std::cout << "[самоприсваивание]\n";
    LivingModule& alias = a;
    a = alias;
    std::cout << "[передача текущего объекта узлу]\n";
    Dock dock{ "D-4" };
    a.PutOnDock(dock);

    // 11. Статические члены
    std::cout << "\n--- 11. Статические члены ---\n";
    std::cout << "Создано модулей (BaseModule::GetCreatedCount()): "
              << BaseModule::GetCreatedCount() << "\n";

    std::cout << "\n===== Конец демонстрации =====\n";
    return 0;
}
