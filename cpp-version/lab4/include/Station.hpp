#pragma once

#include "BaseModule.hpp"
#include "Crew.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace station
{

class Station
{
private:
    std::string m_name;

    // Композиция: станция единолично владеет модулями любых видов.
    // В слотах — указатели на базовый класс.
    std::unique_ptr<std::unique_ptr<BaseModule>[]> m_modules;
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
    [[nodiscard]] int GetTotalPower() const;

    void AddModule(std::unique_ptr<BaseModule> module); // владение передаётся станции
    void AddCrew(const std::shared_ptr<Crew>& crew);
    void Report() const;
};

} // namespace station
