#include "../include/Station.hpp"

#include <iostream>

namespace station
{

Station::Station(std::string_view name)
    : m_name{ name }
{
    m_modules.reserve(10);
    std::cout << "[Station] Станция " << m_name << " создана.\n";
}

Station::~Station()
{
    std::cout << "[Station] Станция " << m_name << " уничтожена.\n";
    // Модули уничтожатся автоматически (композиция).
    // Экипаж НЕ удаляем — он создан вне станции (агрегация).
}

std::string_view Station::GetName() const { return m_name; }

void Station::AddModule(std::string_view name, Module::Type type, int strength)
{
    m_modules.emplace_back(name, type, strength);
    std::cout << "[Station] Модуль " << name << " добавлен на станцию.\n";
}

void Station::AddCrew(Crew* crew)
{
    if (crew == nullptr)
    {
        std::cout << "[Station] Ошибка: нельзя добавить пустого члена экипажа.\n";
        return;
    }
    m_crew.push_back(crew);
    std::cout << "[Station] " << crew->GetName() << " зачислен в экипаж.\n";
}

void Station::Report() const
{
    std::cout << "\n=== Станция " << m_name << " ===\n";
    std::cout << "Модулей: " << m_modules.size() << "\n";
    for (const auto& mod : m_modules)
    {
        std::cout << "  - " << mod.GetName()
                  << " (прочность: " << mod.GetStrength()
                  << (mod.IsBroken() ? ", СЛОМАН" : ", активен")
                  << ")\n";
    }
    std::cout << "Экипаж: " << m_crew.size() << "\n";
    for (const auto* c : m_crew)
    {
        std::cout << "  - " << c->GetName() << "\n";
    }
    std::cout << "=====================\n";
}

} // namespace station
