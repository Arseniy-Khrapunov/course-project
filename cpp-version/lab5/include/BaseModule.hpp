#pragma once

#include "Dock.hpp"
#include "StationExceptions.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace station
{

// Абстрактный базовый класс модуля станции.
// Наследники: LivingModule, LabModule, ReactorModule.
class BaseModule
{
private:
    inline static int m_lastNumber{ 0 }; // статическое поле: счётчик инвентарных номеров

    // m_strength объявлена первой: её проверка выполняется до выдачи номера,
    // поэтому при исключении в конструкторе номер не тратится
    int m_strength{ 0 };
    int m_inventoryNumber{ 0 };
    std::string m_serial{};
    std::string m_name{};
    bool m_broken{ false };
    std::shared_ptr<Dock> m_dock{};

    [[nodiscard]] static std::string MakeSerial(std::string_view prefix, int number);
    [[nodiscard]] static int CheckedStrength(int strength); // бросает InvalidStrengthError

protected:
    // Копирование и перемещение доступны только наследникам и Clone():
    // так базовую часть нельзя случайно «срезать» снаружи.
    BaseModule(const BaseModule& other);
    BaseModule(BaseModule&& other) noexcept;
    BaseModule& operator=(const BaseModule& other);
    BaseModule& operator=(BaseModule&& other) noexcept;

    // Общая часть описания: нужна наследникам, остальному коду — нет
    [[nodiscard]] std::string Header() const;

public:
    BaseModule(std::string_view prefix, std::string_view name, int strength,
               std::shared_ptr<Dock> dock);
    virtual ~BaseModule() noexcept;

    // Чисто виртуальные методы: у каждого наследника своя реализация
    [[nodiscard]] virtual int GetPowerBalance() const = 0;
    [[nodiscard]] virtual std::unique_ptr<BaseModule> Clone() const = 0;

    // Есть реализация, наследник может дополнить или заменить её
    [[nodiscard]] virtual std::string Describe() const;

    // НЕвиртуальный метод: версия выбирается при компиляции по типу ссылки (раннее связывание)
    [[nodiscard]] std::string GetKind() const;

    [[nodiscard]] std::string_view GetName() const;
    [[nodiscard]] std::string_view GetSerial() const;
    [[nodiscard]] int GetStrength() const;
    [[nodiscard]] bool IsBroken() const;
    [[nodiscard]] std::string_view GetDockCode() const;
    [[nodiscard]] long GetDockUseCount() const;

    void Damage(int amount); // бросает InvalidDamageError при amount < 0
    void Repair();
    void RenameDock(std::string_view code);
    void PutOnDock(Dock& dock) const; // передаём текущий объект другому объекту

    // Работа со строками
    [[nodiscard]] std::string GetSerialPrefix() const;     // substr
    [[nodiscard]] std::string GetSerialNumberPart() const; // find + substr
    [[nodiscard]] bool NameContains(std::string_view part) const; // find
    [[nodiscard]] bool SamePrefix(const BaseModule& other) const; // сравнение

    // Статические члены
    [[nodiscard]] static int NextInventoryNumber();
    [[nodiscard]] static int GetCreatedCount();
};

} // namespace station
