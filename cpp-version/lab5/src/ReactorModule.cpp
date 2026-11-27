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

ReactorModule::~ReactorModule() noexcept
{
    std::cout << "  ~ReactorModule(): " << GetName() << "\n";
}

std::string ReactorModule::GetKind() const { return "реактор"; }

// Сломанный или остановленный реактор энергию не выдаёт
int ReactorModule::GetPowerBalance() const
{
    return (IsBroken() || !m_online) ? 0 : m_output;
}

std::string ReactorModule::Describe() const
{
    // заменяет метод базового класса полностью; пользуется protected-методом
    return "Реактор " + Header() + (m_online ? ", в работе" : ", остановлен")
         + ", выдаёт " + std::to_string(GetPowerBalance());
}

std::unique_ptr<BaseModule> ReactorModule::Clone() const
{
    return std::make_unique<ReactorModule>(*this);
}

void ReactorModule::SwitchOn()
{
    if (IsBroken()) // проверка до изменения состояния
    {
        throw ModuleBrokenError{ GetName() };
    }
    m_online = true;
    std::cout << "  [Reactor] " << GetName() << ": запущен\n";
}

void ReactorModule::SwitchOff()
{
    m_online = false;
    std::cout << "  [Reactor] " << GetName() << ": остановлен\n";
}

bool ReactorModule::IsOn() const { return m_online; }

} // namespace station
