#include "../include/Station.hpp"

#include <iostream>

namespace station
{

Station::Station(std::string_view name, std::unique_ptr<IPowerPolicy> policy)
    : m_name{ name }
    , m_moduleCount{ 0 }
    , m_moduleCapacity{ 2 }
    , m_crewCount{ 0 }
    , m_crewCapacity{ 2 }
    , m_policy{ std::move(policy) }
{
    if (!m_policy)
    {
        throw EmptyObjectError{ "политика энергопотребления" };
    }
    m_modules = std::make_unique<std::unique_ptr<BaseModule>[]>(m_moduleCapacity);
    m_crew = std::make_unique<std::weak_ptr<Crew>[]>(m_crewCapacity);
    std::cout << "[Station] Станция " << m_name << " создана (режим: "
              << m_policy->GetName() << ").\n";
}

Station::~Station() noexcept
{
    // Массивы освободятся сами; элементы уничтожаются в обратном порядке
    std::cout << "[Station] Станция " << m_name << " уничтожена.\n";
}

std::string_view Station::GetName() const { return m_name; }

std::string_view Station::GetPolicyName() const { return m_policy->GetName(); }

int Station::GetTotalPower() const
{
    int production = 0;
    int consumption = 0;
    for (int i = 0; i < m_moduleCount; ++i)
    {
        const int balance = m_modules[i]->GetPowerBalance(); // позднее связывание
        if (balance > 0)
        {
            production += balance;
        }
        else
        {
            consumption += -balance;
        }
    }
    // потребление считает объект поведения
    return production - m_policy->AdjustedConsumption(consumption);
}

void Station::SetPolicy(std::unique_ptr<IPowerPolicy> policy)
{
    if (!policy)
    {
        throw EmptyObjectError{ "политика энергопотребления" }; // старая политика не тронута
    }
    m_policy = std::move(policy);
    std::cout << "[Station] Режим энергопотребления: " << m_policy->GetName() << "\n";
}

void Station::GrowModules()
{
    const int newCapacity = m_moduleCapacity * 2;
    auto newArray = std::make_unique<std::unique_ptr<BaseModule>[]>(newCapacity);
    for (int i = 0; i < m_moduleCount; ++i)
    {
        newArray[i] = std::move(m_modules[i]);
    }
    m_modules = std::move(newArray);
    m_moduleCapacity = newCapacity;
}

void Station::GrowCrew()
{
    const int newCapacity = m_crewCapacity * 2;
    auto newArray = std::make_unique<std::weak_ptr<Crew>[]>(newCapacity);
    for (int i = 0; i < m_crewCount; ++i)
    {
        newArray[i] = m_crew[i];
    }
    m_crew = std::move(newArray);
    m_crewCapacity = newCapacity;
}

void Station::AddModule(std::unique_ptr<BaseModule> module)
{
    if (!module)
    {
        throw EmptyObjectError{ "модуль" }; // раньше: сообщение и return
    }
    if (m_moduleCount == m_moduleCapacity)
    {
        GrowModules();
    }
    std::cout << "[Station] Модуль " << module->GetName() << " добавлен на станцию.\n";
    m_modules[m_moduleCount] = std::move(module);
    ++m_moduleCount;
}

void Station::AddCrew(const std::shared_ptr<Crew>& crew)
{
    if (!crew)
    {
        throw EmptyObjectError{ "член экипажа" }; // раньше: сообщение и return
    }
    if (m_crewCount == m_crewCapacity)
    {
        GrowCrew();
    }
    m_crew[m_crewCount] = crew;
    ++m_crewCount;
    std::cout << "[Station] " << crew->GetName() << " зачислен в экипаж.\n";
}

void Station::SwitchOffAll()
{
    std::cout << "[Station] Аварийное отключение:\n";
    for (int i = 0; i < m_moduleCount; ++i)
    {
        // Проверка типа: умеет ли модуль отключаться, базовый класс не говорит
        if (auto* device = dynamic_cast<ISwitchable*>(m_modules[i].get()))
        {
            device->SwitchOff();
        }
        else
        {
            std::cout << "  " << m_modules[i]->GetName()
                      << ": не отключается (нет ISwitchable)\n";
        }
    }
}

void Station::SwitchOnAll()
{
    std::cout << "[Station] Запуск систем:\n";
    for (int i = 0; i < m_moduleCount; ++i)
    {
        if (auto* device = dynamic_cast<ISwitchable*>(m_modules[i].get()))
        {
            try
            {
                device->SwitchOn();
            }
            catch (const ModuleBrokenError& error)
            {
                // Станция может продолжить работу: сломанный модуль просто пропускаем
                std::cout << "  пропущен (" << error.what() << ")\n";
            }
        }
    }
}

void Station::Report() const
{
    std::cout << "\n=== Станция " << m_name << " (режим: " << m_policy->GetName() << ") ===\n";
    std::cout << "Модулей: " << m_moduleCount << "\n";
    for (int i = 0; i < m_moduleCount; ++i)
    {
        std::cout << " - " << m_modules[i]->Describe() << "\n";
    }
    std::cout << "Экипаж: " << m_crewCount << "\n";
    for (int i = 0; i < m_crewCount; ++i)
    {
        if (auto shared = m_crew[i].lock())
        {
            std::cout << " - " << shared->GetName() << "\n";
        }
        else
        {
            std::cout << " - (член экипажа больше не существует)\n";
        }
    }
    std::cout << "Энергобаланс: " << GetTotalPower() << "\n";
    std::cout << "=====================\n";
}

} // namespace station
