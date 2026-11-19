#include "../include/ResearchLog.hpp"

namespace station
{

void ResearchLog::Append(std::string_view entry)
{
    if (!m_text.empty())
    {
        m_text += "; ";
    }
    m_text += entry;
}

std::string_view ResearchLog::GetText() const { return m_text; }

} // namespace station
