#pragma once

#include "Crew.hpp"
#include "Module.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace station
{

class Station
{
private:
    std::string m_name;

    // Композиция: массив модулей по значению (владение)
    std::unique_ptr<Module[]> m_modules;
    int m_moduleCount;
    int m_moduleCapacity;

    // Агрегация: массив weak_ptr для наблюдения за экипажем
    std::unique_ptr<std::weak_ptr<Crew>[]> m_crew;
    int m_crewCount;
    int m_crewCapacity;

    void growModules();
    void growCrew();

public:
    Station(std::string_view name);
    ~Station();

    Station(const Station&)            = delete;
    Station& operator=(const Station&) = delete;
    Station(Station&&)                 = default;
    Station& operator=(Station&&)      = default;

    [[nodiscard]] std::string_view GetName() const;

    void AddModule(std::string_view name, Module::Type type, int strength);
    void AddCrew(const std::shared_ptr<Crew>& crew);
    void Report() const;
};

} // namespace station
