#include "../include/BaseModule.hpp"

#include <algorithm>
#include <iostream>
#include <utility>

namespace station
{

std::string BaseModule::MakeSerial(std::string_view prefix, int number)
{
    std::string digits = std::to_string(number);
    if (digits.size() < 3)
    {
        digits.insert(0, 3 - digits.size(), '0'); // 7 -> "007"
    }
    return std::string{ prefix } + "-" + digits; // конкатенация
}

int BaseModule::CheckedStrength(int strength)
{
    if (strength < 0)
    {
        throw InvalidStrengthError{ strength }; // раньше: сообщение в консоль
    }
    return strength;
}

// ---- конструкторы ----

BaseModule::BaseModule(std::string_view prefix, std::string_view name, int strength,
                       std::shared_ptr<Dock> dock)
    : m_strength{ CheckedStrength(strength) }
    , m_inventoryNumber{ NextInventoryNumber() }
    , m_serial{ MakeSerial(prefix, m_inventoryNumber) }
    , m_name{ name }
    , m_broken{ false }
    , m_dock{ std::move(dock) }
{
    std::cout << "  BaseModule(): " << m_name << " [" << m_serial << "]\n";
}

// Глубокое копирование: у копии свой узел и новый инвентарный номер
BaseModule::BaseModule(const BaseModule& other)
    : m_strength{ other.m_strength }
    , m_inventoryNumber{ NextInventoryNumber() }
    , m_serial{ MakeSerial(other.GetSerialPrefix(), m_inventoryNumber) }
    , m_name{ other.m_name }
    , m_broken{ other.m_broken }
    , m_dock{ other.m_dock ? std::make_shared<Dock>(*other.m_dock) : nullptr }
{
    std::cout << "  BaseModule(copy): " << m_name << " [" << m_serial << "]\n";
}

// Перемещение: забираем данные, номер остаётся прежним (это тот же модуль)
BaseModule::BaseModule(BaseModule&& other) noexcept
    : m_strength{ other.m_strength }
    , m_inventoryNumber{ other.m_inventoryNumber }
    , m_serial{ std::move(other.m_serial) }
    , m_name{ std::move(other.m_name) }
    , m_broken{ other.m_broken }
    , m_dock{ std::move(other.m_dock) }
{
    std::cout << "  BaseModule(move): " << m_name << " [" << m_serial << "]\n";
}

BaseModule::~BaseModule() noexcept
{
    std::cout << "  ~BaseModule(): " << m_name << "\n";
}

// ---- присваивание ----

BaseModule& BaseModule::operator=(const BaseModule& other)
{
    if (this == &other) // самоприсваивание не должно ломать объект
    {
        std::cout << "  BaseModule::operator=: самоприсваивание, пропуск\n";
        return *this;
    }
    m_name = other.m_name;
    m_strength = other.m_strength;
    m_broken = other.m_broken;
    m_dock = other.m_dock ? std::make_shared<Dock>(*other.m_dock) : nullptr; // глубоко
    std::cout << "  BaseModule::operator=(copy): " << m_name << "\n";
    return *this; // позволяет цепочку a = b = c
}

BaseModule& BaseModule::operator=(BaseModule&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    m_name = std::move(other.m_name);
    m_strength = other.m_strength;
    m_broken = other.m_broken;
    m_dock = std::move(other.m_dock);
    std::cout << "  BaseModule::operator=(move): " << m_name << "\n";
    return *this;
}

// ---- описание ----

std::string BaseModule::Header() const
{
    const std::string dock = m_dock ? std::string{ m_dock->GetCode() } : "-";
    return m_name + " [" + m_serial + ", узел " + dock + "]";
}

std::string BaseModule::Describe() const
{
    return Header() + ", прочность " + std::to_string(m_strength)
         + (m_broken ? ", СЛОМАН" : ", активен");
}

std::string BaseModule::GetKind() const { return "модуль станции"; }

std::string_view BaseModule::GetName() const { return m_name; }
std::string_view BaseModule::GetSerial() const { return m_serial; }
int BaseModule::GetStrength() const { return m_strength; }
bool BaseModule::IsBroken() const { return m_broken; }

std::string_view BaseModule::GetDockCode() const
{
    return m_dock ? m_dock->GetCode() : std::string_view{ "-" };
}

long BaseModule::GetDockUseCount() const { return m_dock.use_count(); }

void BaseModule::Damage(int amount)
{
    if (amount < 0) // проверка до изменения состояния: строгая гарантия
    {
        throw InvalidDamageError{ amount };
    }
    m_strength = std::max(0, m_strength - amount); // прочность не уходит в минус
    if (m_strength == 0)
    {
        m_broken = true;
        std::cout << "[Module] Модуль " << m_name << " сломан!\n";
    }
}

void BaseModule::Repair()
{
    m_strength = 100;
    m_broken = false;
    std::cout << "[Module] Модуль " << m_name << " отремонтирован.\n";
}

void BaseModule::RenameDock(std::string_view code)
{
    if (m_dock)
    {
        m_dock->SetCode(code);
    }
}

void BaseModule::PutOnDock(Dock& dock) const
{
    dock.Register(*this); // *this — текущий объект передаётся другому объекту
}

// ---- строки ----

std::string BaseModule::GetSerialPrefix() const
{
    return m_serial.substr(0, m_serial.find('-')); // "LAB-002" -> "LAB"
}

std::string BaseModule::GetSerialNumberPart() const
{
    const std::size_t pos = m_serial.find('-');
    if (pos == std::string::npos)
    {
        return {};
    }
    return m_serial.substr(pos + 1); // "LAB-002" -> "002"
}

bool BaseModule::NameContains(std::string_view part) const
{
    return m_name.find(part) != std::string::npos;
}

bool BaseModule::SamePrefix(const BaseModule& other) const
{
    return GetSerialPrefix() == other.GetSerialPrefix();
}

// ---- статические члены ----

int BaseModule::NextInventoryNumber() { return ++m_lastNumber; }
int BaseModule::GetCreatedCount() { return m_lastNumber; }

} // namespace station
