#pragma once

#include "BaseModule.hpp"
#include "ISwitchable.hpp"
#include "ResearchLog.hpp"

namespace station
{

// Лаборатория: наследует состояние от BaseModule и обязуется выполнить контракт ISwitchable
class LabModule : public BaseModule, public ISwitchable
{
private:
    std::string m_field{};
    bool m_online{ true };
    // Журнал общий для копий лаборатории: копирование по умолчанию — поверхностное
    std::shared_ptr<ResearchLog> m_log{};

public:
    LabModule(std::string_view name, int strength,
              std::shared_ptr<Dock> dock, std::string_view field);

    LabModule(const LabModule& other) = default;
    LabModule(LabModule&& other) noexcept = default;
    LabModule& operator=(const LabModule& other) = default;
    LabModule& operator=(LabModule&& other) noexcept = default;
    ~LabModule() noexcept override;

    // BaseModule
    [[nodiscard]] std::string GetKind() const; // скрывает BaseModule::GetKind (не override)
    [[nodiscard]] int GetPowerBalance() const override;
    [[nodiscard]] std::string Describe() const override;
    [[nodiscard]] std::unique_ptr<BaseModule> Clone() const override;

    // ISwitchable
    void SwitchOn() override;
    void SwitchOff() override;
    [[nodiscard]] bool IsOn() const override;

    void WriteLog(std::string_view entry);
    [[nodiscard]] long GetLogUseCount() const;
};

} // namespace station
