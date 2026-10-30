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
    // Композиция: станция единолично владеет модулями.
    // Массив хранит умные указатели, а не сами модули: при росте массива
    // переезжают только указатели, и деструкторы модулей не вызываются зря.
    std::unique_ptr<std::unique_ptr<Module>[]> m_modules;
    int m_moduleCount;
    int m_moduleCapacity;

    // Агрегация: станция только наблюдает за экипажем
    std::unique_ptr<std::weak_ptr<Crew>[]> m_crew;
    int m_crewCount;
    int m_crewCapacity;

    void GrowModules();
    void GrowCrew();

public:
    explicit Station(std::string_view name);
    ~Station();
    Station(const Station&) = delete;
    Station& operator=(const Station&) = delete;
    Station(Station&&) = default;
    Station& operator=(Station&&) = default;
    [[nodiscard]] std::string_view GetName() const;
    void AddModule(std::string_view name, Module::Type type, int strength);
    void AddCrew(const std::shared_ptr<Crew>& crew);
    void Report() const;
};
}
