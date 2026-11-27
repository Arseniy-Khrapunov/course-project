#include "../include/LivingModule.hpp"

#include <iostream>

namespace station
{

LivingModule::LivingModule()
    : BaseModule{ "LIV", "Без названия", 100, std::make_shared<Dock>("-") }
    , m_capacity{ 1 }
{
    std::cout << "  LivingModule(): " << GetName() << "\n";
}

LivingModule::LivingModule(std::string_view name, int strength,
                           std::shared_ptr<Dock> dock, int capacity)
    : BaseModule{ "LIV", name, strength, std::move(dock) } // сначала — база
    , m_capacity{ capacity }
{
    std::cout << "  LivingModule(): " << GetName() << ", мест " << m_capacity << "\n";
}

LivingModule::~LivingModule() noexcept
{
    std::cout << "  ~LivingModule(): " << GetName() << "\n";
}

std::string LivingModule::GetKind() const { return "жилой модуль"; }

int LivingModule::GetPowerBalance() const { return -5 * m_capacity; }

std::string LivingModule::Describe() const
{
    // дополняет метод базового класса
    return BaseModule::Describe() + ", мест: " + std::to_string(m_capacity);
}

std::unique_ptr<BaseModule> LivingModule::Clone() const
{
    return std::make_unique<LivingModule>(*this); // конструктор копирования
}

int LivingModule::GetCapacity() const { return m_capacity; }

} // namespace station
