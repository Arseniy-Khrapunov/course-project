#pragma once

#include "IPowerPolicy.hpp"

namespace station
{

// Форсированный режим: потребление вырастает до 150 %
class BoostPower final : public IPowerPolicy
{
private:
    static constexpr int PERCENT = 150;

public:
    [[nodiscard]] int AdjustedConsumption(int units) const override
    {
        return units * PERCENT / 100;
    }

    [[nodiscard]] std::string_view GetName() const override
    {
        return "форсированный";
    }
};

} // namespace station
