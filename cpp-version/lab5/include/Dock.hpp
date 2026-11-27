#pragma once

#include <string>
#include <string_view>

namespace station
{

class BaseModule; // предварительное объявление: стыковочному узлу нужен только тип

// Стыковочный узел, к которому подключён модуль.
// Правило нуля: полей, требующих особого копирования, нет — операции не пишем.
class Dock
{
private:
    std::string m_code{};

public:
    explicit Dock(std::string_view code);

    [[nodiscard]] std::string_view GetCode() const;
    void SetCode(std::string_view code);

    // Принимает модуль на узел (получает ссылку на текущий объект модуля)
    void Register(const BaseModule& module) const;
};

} // namespace station
