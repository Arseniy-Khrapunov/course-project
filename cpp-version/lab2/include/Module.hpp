#pragma once

#include <string>
#include <string_view>

namespace station
{

// Модуль станции. Часть станции (композиция).
// Не существует без станции: уничтожили станцию — модуль исчез.
class Module
{
public:
    enum class Type
    {
        eLiving,    // жилой
        eLab,       // лаборатория
        eReactor    // реактор
    };

private:
    std::string m_name;
    Type        m_type;
    int         m_strength;    // прочность 0..100
    bool        m_broken;

public:
    Module(std::string_view name, Type type, int strength);
    ~Module();

    Module(const Module&)            = delete;
    Module& operator=(const Module&) = delete;
    Module(Module&&)                 = default;
    Module& operator=(Module&&)      = default;

    [[nodiscard]] std::string_view GetName() const;
    [[nodiscard]] Type             GetType() const;
    [[nodiscard]] int              GetStrength() const;
    [[nodiscard]] bool             IsBroken() const;

    // Содержательный метод: повредить модуль
    void Damage(int amount);

    // Содержательный метод: отремонтировать модуль
    void Repair();

    // Проверка правила: прочность не может быть отрицательной
    void CheckStrength() const;
};

} // namespace station
