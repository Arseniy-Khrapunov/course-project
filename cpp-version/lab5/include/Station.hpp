#pragma once

#include "BaseModule.hpp"
#include "Crew.hpp"
#include "IPowerPolicy.hpp"
#include "ISwitchable.hpp"
#include "StationExceptions.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace station
{

class Station
{
private:
    std::string m_name;

    // Композиция: станция единолично владеет модулями любых видов
    std::unique_ptr<std::unique_ptr<BaseModule>[]> m_modules;
    int m_moduleCount;
    int m_moduleCapacity;

    // Агрегация: станция только наблюдает за экипажем
    std::unique_ptr<std::weak_ptr<Crew>[]> m_crew;
    int m_crewCount;
    int m_crewCapacity;

    // Объект поведения: как считать потребление энергии (конфигурирование)
    std::unique_ptr<IPowerPolicy> m_policy;

    void GrowModules();
    void GrowCrew();

public:
    // Статическое конфигурирование: политика задаётся при создании.
    // Бросает EmptyObjectError, если политика пуста.
    Station(std::string_view name, std::unique_ptr<IPowerPolicy> policy);
    ~Station() noexcept;
    Station(const Station&) = delete;
    Station& operator=(const Station&) = delete;
    Station(Station&&) noexcept = default;
    Station& operator=(Station&&) noexcept = default;

    [[nodiscard]] std::string_view GetName() const;
    [[nodiscard]] int GetTotalPower() const;
    [[nodiscard]] std::string_view GetPolicyName() const;

    // Динамическое конфигурирование: политику можно заменить во время работы.
    // Бросает EmptyObjectError; при исключении прежняя политика остаётся.
    void SetPolicy(std::unique_ptr<IPowerPolicy> policy);

    // Оба бросают EmptyObjectError при пустом аргументе
    void AddModule(std::unique_ptr<BaseModule> module);
    void AddCrew(const std::shared_ptr<Crew>& crew);

    // Проверка типа во время выполнения: отключается только то, что реализует ISwitchable
    void SwitchOffAll();
    void SwitchOnAll(); // сломанные модули пропускает, перехватывая ModuleBrokenError

    void Report() const;
};

} // namespace station
