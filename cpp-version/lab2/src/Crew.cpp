#include "../include/Crew.hpp"

#include <iostream>

namespace station
{

Crew::Crew(std::string_view name, Role role)
    : m_name{ name }
    , m_role{ role }
    , m_state{ State::eHealthy }
{
    std::cout << "[Crew] Принят на станцию: " << m_name << "\n";
}

Crew::~Crew()
{
    std::cout << "[Crew] Покинул станцию: " << m_name << "\n";
}

std::string_view Crew::GetName() const { return m_name; }
Crew::Role Crew::GetRole() const { return m_role; }
Crew::State Crew::GetState() const { return m_state; }

void Crew::Wound()
{
    if (m_state == State::eDead)
    {
        std::cout << "[Crew] Ошибка: мёртвого нельзя ранить повторно.\n";
        return;
    }
    m_state = State::eWounded;
    std::cout << "[Crew] " << m_name << " ранен.\n";
}

void Crew::Heal()
{
    if (m_state == State::eDead)
    {
        std::cout << "[Crew] Ошибка: мёртвого нельзя вылечить!\n";
        return;
    }
    m_state = State::eHealthy;
    std::cout << "[Crew] " << m_name << " вылечен.\n";
}

void Crew::CheckAlive() const
{
    if (m_state == State::eDead)
    {
        std::cout << "[Crew] Ошибка: " << m_name << " мёртв.\n";
    }
}

} // namespace station
