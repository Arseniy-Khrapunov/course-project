#pragma once
#include <string>
#include <string_view>
namespace station
{
class Crew
{
public:
    enum class Role { eEngineer, eScientist, eDoctor };
    enum class State { eHealthy, eWounded, eDead };
private:
    std::string m_name;
    Role m_role;
    State m_state;
public:
    Crew(std::string_view name, Role role);
    ~Crew();
    Crew(const Crew&) = delete;
    Crew& operator=(const Crew&) = delete;
    Crew(Crew&&) = delete;
    Crew& operator=(Crew&&) = delete;
    [[nodiscard]] std::string_view GetName() const;
    [[nodiscard]] Role GetRole() const;
    [[nodiscard]] State GetState() const;
    void Wound();
    void Heal();
    void CheckAlive() const;
};
}
