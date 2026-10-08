#include "../include/Module.hpp"

#include <iostream>

namespace station
{

Module::Module(std::string_view name, Type type, int strength)
    : m_name{ name }
    , m_type{ type }
    , m_strength{ strength }
    , m_broken{ false }
{
    std::cout << "[Module] Создан модуль: " << m_name << "\n";
    CheckStrength();
}

Module::~Module()
{
    std::cout << "[Module] Уничтожен модуль: " << m_name << "\n";
}

std::string_view Module::GetName() const { return m_name; }
Module::Type Module::GetType() const { return m_type; }
int Module::GetStrength() const { return m_strength; }
bool Module::IsBroken() const { return m_broken; }

void Module::Damage(int amount)
{
    m_strength -= amount;
    CheckStrength();

    if (m_strength <= 0)
    {
        m_broken = true;
        std::cout << "[Module] Модуль " << m_name << " сломан!\n";
    }
}

void Module::Repair()
{
    m_strength = 100;
    m_broken   = false;
    std::cout << "[Module] Модуль " << m_name << " отремонтирован.\n";
}

void Module::CheckStrength() const
{
    if (m_strength < 0)
    {
        std::cout << "[Module] Ошибка: прочность не может быть отрицательной!\n";
    }
}

} // namespace station
