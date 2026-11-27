#pragma once

#include "IPowerPolicy.hpp"

namespace station
{

// Обычный режим: потребление без изменений
class StandardPower final : public IPowerPolicy
{
public:
    [[nodiscard]] int AdjustedConsumption(int units) const override
    {
        return units;
    }

    [[nodiscard]] std::string_view GetName() const override
    {
        return "стандартный";
    }
};

} // namespace station
