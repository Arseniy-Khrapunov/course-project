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
    // Создаем массивы через make_unique (без new)
    m_modules = std::make_unique<Module[]>(m_moduleCapacity);
    m_crew    = std::make_unique<std::weak_ptr<Crew>[]>(m_crewCapacity);
    std::cout << "[Station] Станция " << m_name << " создана.\n";
}

Station::~Station()
{
    // delete не нужен, unique_ptr сам освободит память
    std::cout << "[Station] Станция " << m_name << " уничтожена.\n";
}

std::string_view Station::GetName() const { return m_name; }

void Station::growModules()
{
    int newCap = m_moduleCapacity * 2;
    auto newArr = std::make_unique<Module[]>(newCap);
    for (int i = 0; i < m_moduleCount; ++i) {
        newArr[i] = std::move(m_modules[i]);
    }
    m_modules = std::move(newArr);
    m_moduleCapacity = newCap;
}

void Station::growCrew()
{
    int newCap = m_crewCapacity * 2;
    auto newArr = std::make_unique<std::weak_ptr<Crew>[]>(newCap);
    for (int i = 0; i < m_crewCount; ++i) {
        newArr[i] = m_crew[i];
    }
    m_crew = std::move(newArr);
    m_crewCapacity = newCap;
}

void Station::AddModule(std::string_view name, Module::Type type, int strength)
{
    if (m_moduleCount == m_moduleCapacity) growModules();
    m_modules[m_moduleCount] = Module(name, type, strength);
    ++m_moduleCount;
    std::cout << "[Station] Модуль " << name << " добавлен на станцию.\n";
}

void Station::AddCrew(const std::shared_ptr<Crew>& crew)
{
    if (!crew) return;
    if (m_crewCount == m_crewCapacity) growCrew();
    m_crew[m_crewCount] = crew; // shared_ptr неявно преобразуется в weak_ptr
    ++m_crewCount;
    std::cout << "[Station] " << crew->GetName() << " зачислен в экипаж.\n";
}

void Station::Report() const
{
    std::cout << "\n=== Станция " << m_name << " ===\n";
    std::cout << "Модулей: " << m_moduleCount << "\n";
    for (int i = 0; i < m_moduleCount; ++i) {
        std::cout << "  - " << m_modules[i].GetName() << "\n";
    }
    std::cout << "Экипаж: " << m_crewCount << "\n";
    for (int i = 0; i < m_crewCount; ++i) {
        if (auto shared = m_crew[i].lock()) {
            std::cout << "  - " << shared->GetName() << "\n";
        } else {
            std::cout << "  - (член экипажа больше не существует)\n";
        }
    }
    std::cout << "=====================\n";
}

} // namespace station
