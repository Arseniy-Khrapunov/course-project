#pragma once

#include "BaseModule.hpp"
#include "ResearchLog.hpp"

namespace station
{

// Лаборатория: потребляет много энергии, ведёт общий журнал исследований
class LabModule : public BaseModule
{
private:
    std::string m_field{};
    // Журнал общий для копий лаборатории — копирование по умолчанию
    // даёт поверхностную копию (копии делят один журнал)
    std::shared_ptr<ResearchLog> m_log{};

public:
    LabModule(std::string_view name, int strength,
              std::shared_ptr<Dock> dock, std::string_view field);

    LabModule(const LabModule& other) = default;
    LabModule(LabModule&& other) noexcept = default;
    LabModule& operator=(const LabModule& other) = default;
    LabModule& operator=(LabModule&& other) noexcept = default;
    ~LabModule() override;

    [[nodiscard]] int GetPowerBalance() const override;
    [[nodiscard]] std::string Describe() const override; // с вызовом базового
    [[nodiscard]] std::unique_ptr<BaseModule> Clone() const override;

    void WriteLog(std::string_view entry);
    [[nodiscard]] long GetLogUseCount() const;
};

} // namespace station
