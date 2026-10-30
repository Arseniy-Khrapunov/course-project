#include "../include/Station.hpp"

#include <iostream>

namespace station
{

Station::Station(std::string_view name)
    : m_name{ name }
    , m_moduleCount{ 0 }
    , m_moduleCapacity{ 2 }
    , m_crewCount{ 0 }
    , m_crewCapacity{ 2 }
{
    m_modules = std::make_unique<std::unique_ptr<Module>[]>(m_moduleCapacity);
    m_crew = std::make_unique<std::weak_ptr<Crew>[]>(m_crewCapacity);
    std::cout << "[Station] Станция " << m_name << " создана.\n";
}

Station::~Station()
{
    // Массивы освободятся сами; элементы уничтожаются в обратном порядке
    std::cout << "[Station] Станция " << m_name << " уничтожена.\n";
}

std::string_view Station::GetName() const { return m_name; }

void Station::GrowModules()
{
    const int newCapacity = m_moduleCapacity * 2;
    auto newArray = std::make_unique<std::unique_ptr<Module>[]>(newCapacity);
    for (int i = 0; i < m_moduleCount; ++i)
    {
        newArray[i] = std::move(m_modules[i]); // переезжает указатель, не модуль
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

void Station::AddModule(std::string_view name, Module::Type type, int strength)
{
    if (m_moduleCount == m_moduleCapacity)
    {
        GrowModules();
    }
    m_modules[m_moduleCount] = std::make_unique<Module>(name, type, strength);
    ++m_moduleCount;
    std::cout << "[Station] Модуль " << name << " добавлен на станцию.\n";
}

void Station::AddCrew(const std::shared_ptr<Crew>& crew)
{
    if (!crew)
    {
        std::cout << "[Station] Ошибка: нельзя добавить пустого члена экипажа.\n";
        return;
    }
    if (m_crewCount == m_crewCapacity)
    {
        GrowCrew();
    }
    m_crew[m_crewCount] = crew; // shared_ptr неявно преобразуется в weak_ptr
    ++m_crewCount;
    std::cout << "[Station] " << crew->GetName() << " зачислен в экипаж.\n";
}

void Station::Report() const
{
    std::cout << "\n=== Станция " << m_name << " ===\n";
    std::cout << "Модулей: " << m_moduleCount << "\n";
    for (int i = 0; i < m_moduleCount; ++i)
    {
        std::cout << " - " << m_modules[i]->GetName() << "\n";
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
    std::cout << "=====================\n";
}

} // namespace station
