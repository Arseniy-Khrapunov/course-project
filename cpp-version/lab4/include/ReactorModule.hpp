#pragma once

#include "BaseModule.hpp"

namespace station
{

// Реактор: единственный источник энергии. От него не наследуются.
class ReactorModule final : public BaseModule
{
private:
    int m_output{ 0 };

public:
    ReactorModule(std::string_view name, int strength,
                  std::shared_ptr<Dock> dock, int output);

    ReactorModule(const ReactorModule& other) = default;
    ReactorModule(ReactorModule&& other) noexcept = default;
    ReactorModule& operator=(const ReactorModule& other) = default;
    ReactorModule& operator=(ReactorModule&& other) noexcept = default;
    ~ReactorModule() override;

    [[nodiscard]] int GetPowerBalance() const override;
    [[nodiscard]] std::string Describe() const override; // без вызова базового
    [[nodiscard]] std::unique_ptr<BaseModule> Clone() const override;
};

} // namespace station
