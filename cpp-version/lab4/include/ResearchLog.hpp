#pragma once

#include <string>
#include <string_view>

namespace station
{

// Журнал исследований лаборатории.
// Правило нуля: копирование и освобождение выполняет std::string.
class ResearchLog
{
private:
    std::string m_text{};

public:
    void Append(std::string_view entry);
    [[nodiscard]] std::string_view GetText() const;
};

} // namespace station
