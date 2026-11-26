#include "../include/Dock.hpp"

#include "../include/BaseModule.hpp"

#include <iostream>

namespace station
{

Dock::Dock(std::string_view code)
    : m_code{ code }
{}

std::string_view Dock::GetCode() const { return m_code; }

void Dock::SetCode(std::string_view code) { m_code = code; }

void Dock::Register(const BaseModule& module) const
{
    std::cout << "[Dock] Узел " << m_code << ": принят модуль "
              << module.GetSerial() << "\n";
}

} // namespace station
