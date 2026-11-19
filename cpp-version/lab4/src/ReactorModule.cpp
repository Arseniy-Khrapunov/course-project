#include "../include/ReactorModule.hpp"

#include <iostream>

namespace station
{

ReactorModule::ReactorModule(std::string_view name, int strength,
                             std::shared_ptr<Dock> dock, int output)
    : BaseModule{ "REA", name, strength, std::move(dock) }
    , m_output{ output }
{
    std::cout << "  ReactorModule(): " << GetName() << ", мощность " << m_output << "\n";
}

ReactorModule::~ReactorModule()
{
    std::cout << "  ~ReactorModule(): " << GetName() << "\n";
}

// Сломанный реактор энергию не выдаёт
int ReactorModule::GetPowerBalance() const { return IsBroken() ? 0 : m_output; }

std::string ReactorModule::Describe() const
{
    // заменяет метод базового класса полностью; пользуется protected-методом
    return "Реактор " + Header() + ", выдаёт " + std::to_string(GetPowerBalance());
}

std::unique_ptr<BaseModule> ReactorModule::Clone() const
{
    return std::make_unique<ReactorModule>(*this);
}

} // namespace station
