#pragma once

#include "IPowerPolicy.hpp"

namespace station
{

// Экономный режим: потребление снижено до 60 %
class EconomyPower final : public IPowerPolicy
{
private:
    static constexpr int PERCENT = 60;

public:
    [[nodiscard]] int AdjustedConsumption(int units) const override
    {
        return units * PERCENT / 100;
    }

    [[nodiscard]] std::string_view GetName() const override
    {
        return "экономный";
    }
};

} // namespace station
