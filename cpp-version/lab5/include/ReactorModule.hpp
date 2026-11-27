#pragma once

#include "BaseModule.hpp"
#include "ISwitchable.hpp"

namespace station
{

// Реактор: единственный источник энергии. От него не наследуются.
class ReactorModule final : public BaseModule, public ISwitchable
{
private:
    int m_output{ 0 };
    bool m_online{ true };

public:
    ReactorModule(std::string_view name, int strength,
                  std::shared_ptr<Dock> dock, int output);

    ReactorModule(const ReactorModule& other) = default;
    ReactorModule(ReactorModule&& other) noexcept = default;
    ReactorModule& operator=(const ReactorModule& other) = default;
    ReactorModule& operator=(ReactorModule&& other) noexcept = default;
    ~ReactorModule() noexcept override;

    // BaseModule
    [[nodiscard]] std::string GetKind() const; // скрывает BaseModule::GetKind (не override)
    [[nodiscard]] int GetPowerBalance() const override;
    [[nodiscard]] std::string Describe() const override; // без вызова базового
    [[nodiscard]] std::unique_ptr<BaseModule> Clone() const override;

    // ISwitchable
    void SwitchOn() override;
    void SwitchOff() override;
    [[nodiscard]] bool IsOn() const override;
};

} // namespace station
