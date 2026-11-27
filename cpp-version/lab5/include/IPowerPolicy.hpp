#pragma once

#include <string_view>

namespace station
{

// Интерфейс объекта поведения: как станция считает потребление энергии
class IPowerPolicy
{
public:
    virtual ~IPowerPolicy() noexcept = default;

    // Сколько единиц энергии реально потребуется при базовом потреблении units
    [[nodiscard]] virtual int AdjustedConsumption(int units) const = 0;
    [[nodiscard]] virtual std::string_view GetName() const = 0;
};

} // namespace station
