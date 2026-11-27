#include "../include/LabModule.hpp"

#include <iostream>

namespace station
{

LabModule::LabModule(std::string_view name, int strength,
                     std::shared_ptr<Dock> dock, std::string_view field)
    : BaseModule{ "LAB", name, strength, std::move(dock) }
    , m_field{ field }
    , m_log{ std::make_shared<ResearchLog>() }
{
    std::cout << "  LabModule(): " << GetName() << ", направление " << m_field << "\n";
}

LabModule::~LabModule() noexcept
{
    std::cout << "  ~LabModule(): " << GetName() << "\n";
}

std::string LabModule::GetKind() const { return "лаборатория"; }

int LabModule::GetPowerBalance() const { return m_online ? -30 : 0; }

std::string LabModule::Describe() const
{
    const std::string_view text = m_log->GetText();
    return BaseModule::Describe() + ", направление: " + m_field
         + (m_online ? ", включена" : ", отключена")
         + ", журнал: " + (text.empty() ? std::string{ "пуст" } : std::string{ text });
}

std::unique_ptr<BaseModule> LabModule::Clone() const
{
    return std::make_unique<LabModule>(*this);
}

void LabModule::SwitchOn()
{
    if (IsBroken()) // проверка до изменения состояния: при исключении объект не изменился
    {
        throw ModuleBrokenError{ GetName() };
    }
    m_online = true;
    std::cout << "  [Lab] " << GetName() << ": включена\n";
}

void LabModule::SwitchOff()
{
    m_online = false;
    std::cout << "  [Lab] " << GetName() << ": отключена\n";
}

bool LabModule::IsOn() const { return m_online; }

void LabModule::WriteLog(std::string_view entry) { m_log->Append(entry); }

long LabModule::GetLogUseCount() const { return m_log.use_count(); }

} // namespace station
