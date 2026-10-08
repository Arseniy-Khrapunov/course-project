#pragma once

#include "Crew.hpp"
#include "Module.hpp"

#include <string>
#include <string_view>
#include <vector>

namespace station
{

// Станция. Содержит модули (композиция) и агрегирует экипаж.
class Station
{
private:
    std::string         m_name;
    std::vector<Module> m_modules;   // композиция: модули — часть станции
    std::vector<Crew*>  m_crew;      // агрегация: экипаж создан вне станции

public:
    Station(std::string_view name);
    ~Station();

    Station(const Station&)            = delete;
    Station& operator=(const Station&) = delete;
    Station(Station&&)                 = default;
    Station& operator=(Station&&)      = default;

    [[nodiscard]] std::string_view GetName() const;

    // Содержательный метод: добавить модуль (композиция)
    void AddModule(std::string_view name, Module::Type type, int strength);

    // Содержательный метод: добавить члена экипажа (агрегация)
    void AddCrew(Crew* crew);

    // Содержательный метод: показать отчёт
    void Report() const;
};

} // namespace station
