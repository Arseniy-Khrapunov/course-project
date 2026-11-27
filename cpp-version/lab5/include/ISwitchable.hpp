#pragma once

namespace station
{

// Интерфейс: «устройство можно включать и отключать».
// Только чисто виртуальные методы и виртуальный деструктор, полей нет.
class ISwitchable
{
public:
    virtual ~ISwitchable() noexcept = default;

    virtual void SwitchOn() = 0;                   // может бросить ModuleBrokenError
    virtual void SwitchOff() = 0;
    [[nodiscard]] virtual bool IsOn() const = 0;
};

} // namespace station
