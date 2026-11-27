#include "../include/BoostPower.hpp"
#include "../include/Crew.hpp"
#include "../include/EconomyPower.hpp"
#include "../include/ISwitchable.hpp"
#include "../include/LabModule.hpp"
#include "../include/LivingModule.hpp"
#include "../include/ReactorModule.hpp"
#include "../include/StandardPower.hpp"
#include "../include/Station.hpp"
#include "../include/StationExceptions.hpp"

#include <iostream>
#include <memory>
#include <typeinfo>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace station;

namespace
{

// Работает через интерфейс и не знает, какой именно класс перед ней
void EmergencyShutdown(ISwitchable& device)
{
    if (device.IsOn())
    {
        device.SwitchOff();
    }
}

// Проверка типа: отключить можно только то, что реализует ISwitchable
void TrySwitchOff(BaseModule& module)
{
    if (auto* device = dynamic_cast<ISwitchable*>(&module))
    {
        device->SwitchOff();
    }
    else
    {
        std::cout << "  " << module.GetName() << ": отключить нельзя — не реализует ISwitchable\n";
    }
}

// Исключение перехватывается там, где понятно, что делать: починить и повторить
void SwitchOnWithRepair(BaseModule& module)
{
    auto* device = dynamic_cast<ISwitchable*>(&module);
    if (device == nullptr)
    {
        return;
    }
    try
    {
        device->SwitchOn();
    }
    catch (const ModuleBrokenError& error)
    {
        std::cout << "  Ошибка: " << error.what() << " — ремонтируем и повторяем\n";
        module.Repair();
        device->SwitchOn();
    }
}

} // namespace

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << std::boolalpha;
    std::cout << "===== ЛР 5. Полиморфизм =====\n";

    LabModule lab{ "Лаборатория", 90, std::make_shared<Dock>("B-2"), "биология" };
    ReactorModule reactor{ "Реактор-1", 100, std::make_shared<Dock>("R-1"), 120 };
    LivingModule living{ "Жилой отсек", 100, std::make_shared<Dock>("A-1"), 4 };

    // 1. Интерфейс: функция работает через ISwitchable
    std::cout << "\n--- 1. Интерфейс ISwitchable ---\n";
    EmergencyShutdown(lab);
    EmergencyShutdown(reactor);
    std::cout << "lab.IsOn(): " << lab.IsOn() << ", reactor.IsOn(): " << reactor.IsOn() << "\n";

    // 2. Множественное наследование: один объект виден и как BaseModule, и как ISwitchable
    std::cout << "\n--- 2. Множественное наследование ---\n";
    BaseModule& asModule = lab;
    ISwitchable& asDevice = lab;
    std::cout << "Как BaseModule: " << asModule.GetName() << " [" << asModule.GetSerial() << "]\n";
    std::cout << "Как ISwitchable: включена = " << asDevice.IsOn() << "\n";

    // 3. Раннее и позднее связывание
    std::cout << "\n--- 3. Раннее и позднее связывание ---\n";
    lab.SwitchOn();
    std::cout << "lab.GetKind() (тип LabModule):       " << lab.GetKind() << "\n";
    std::cout << "asModule.GetKind() (BaseModule&):    " << asModule.GetKind()
              << "   <- раннее: по типу ссылки\n";
    std::cout << "asModule.Describe() (BaseModule&):\n  " << asModule.Describe()
              << "\n   ^ позднее: по настоящему типу объекта\n";
    const BaseModule& livingRef = living;
    std::cout << "living.GetKind(): " << living.GetKind()
              << ", livingRef.GetKind(): " << livingRef.GetKind() << "\n";

    // 4. Проверка типа во время выполнения
    std::cout << "\n--- 4. dynamic_cast ---\n";
    TrySwitchOff(living);
    TrySwitchOff(lab);
    try
    {
        ISwitchable& device = dynamic_cast<ISwitchable&>(living); // ссылка: исключение
        device.SwitchOff();
    }
    catch (const std::bad_cast& error)
    {
        std::cout << "  dynamic_cast к ссылке бросил исключение: " << error.what() << "\n";
    }

    // 5. Конфигурирование: объект поведения IPowerPolicy
    std::cout << "\n--- 5. Конфигурирование станции ---\n";
    Station station{ "МКС-1", std::make_unique<StandardPower>() }; // статически
    station.AddModule(std::make_unique<ReactorModule>("Реактор-2", 100,
                                                      std::make_shared<Dock>("R-2"), 120));
    auto spare = std::make_unique<ReactorModule>("Резервный реактор", 100,
                                                 std::make_shared<Dock>("R-3"), 80);
    spare->Damage(100); // сломан
    station.AddModule(std::move(spare));
    station.AddModule(std::make_unique<LivingModule>("Жилой отсек-2", 100,
                                                     std::make_shared<Dock>("A-2"), 4));
    station.AddModule(std::make_unique<LabModule>("Лаборатория-2", 95,
                                                  std::make_shared<Dock>("B-3"), "химия"));
    station.Report();
    station.SetPolicy(std::make_unique<EconomyPower>()); // динамически
    std::cout << "Энергобаланс: " << station.GetTotalPower() << "\n";
    station.SetPolicy(std::make_unique<BoostPower>());
    std::cout << "Энергобаланс: " << station.GetTotalPower() << "\n";
    station.SetPolicy(std::make_unique<StandardPower>());
    station.SwitchOffAll();
    std::cout << "Энергобаланс после отключения: " << station.GetTotalPower() << "\n";
    station.SwitchOnAll();
    std::cout << "Энергобаланс после запуска: " << station.GetTotalPower() << "\n";

    // 6. Исключения
    std::cout << "\n--- 6. Исключения ---\n";
    std::cout << "[6.1 нарушение правила при создании; свёртка стека]\n";
    try
    {
        LivingModule temp{ "Временный", 50, std::make_shared<Dock>("T-1"), 2 };
        LabModule broken{ "Брак", -10, std::make_shared<Dock>("T-2"), "химия" };
        std::cout << "  сюда управление не дойдёт\n";
    }
    catch (const InvalidStrengthError& error)
    {
        std::cout << "  Перехвачено нарушение правила: " << error.what() << "\n";
        std::cout << "  Выдано номеров: " << BaseModule::GetCreatedCount()
                  << " (номер неудавшегося модуля не потрачен)\n";
    }
    catch (const std::exception& error)
    {
        std::cout << "  Другая ошибка: " << error.what() << "\n";
    }

    std::cout << "[6.2 отрицательный урон; порядок catch: частный -> общий]\n";
    try
    {
        living.Damage(20);
        std::cout << "  урон 20 нанесён, прочность " << living.GetStrength() << "\n";
        living.Damage(-5);
    }
    catch (const InvalidDamageError& error)
    {
        std::cout << "  Перехвачено нарушение правила: " << error.what() << "\n";
    }
    catch (const std::logic_error& error)
    {
        std::cout << "  Логическая ошибка: " << error.what() << "\n";
    }
    catch (const std::exception& error)
    {
        std::cout << "  Ошибка: " << error.what() << "\n";
    }

    std::cout << "[6.3 сломанный реактор: перехват, ремонт и повтор]\n";
    reactor.Damage(100);
    SwitchOnWithRepair(reactor);

    std::cout << "[6.4 пустой модуль]\n";
    try
    {
        station.AddModule(nullptr);
    }
    catch (const EmptyObjectError& error)
    {
        std::cout << "  Перехвачено нарушение правила: " << error.what() << "\n";
    }

    std::cout << "[6.5 погибший член экипажа]\n";
    auto engineer = std::make_shared<Crew>("Иванов", Crew::Role::eEngineer);
    station.AddCrew(engineer);
    try
    {
        engineer->Wound();
        engineer->Heal();
        engineer->Kill();
        engineer->Heal();
    }
    catch (const DeadCrewError& error)
    {
        std::cout << "  Перехвачено нарушение правила: " << error.what() << "\n";
    }

    std::cout << "\n===== Конец демонстрации =====\n";
    return 0;
}
