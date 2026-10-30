#pragma once
#include <string>
#include <string_view>
namespace station
{
class Module
{
public:
    enum class Type { eLiving, eLab, eReactor };
private:
    std::string m_name;
    Type m_type;
    int m_strength;
    bool m_broken;
public:
    Module(std::string_view name, Type type, int strength);
    ~Module();
    Module(const Module&) = delete;
    Module& operator=(const Module&) = delete;
    [[nodiscard]] std::string_view GetName() const;
    [[nodiscard]] Type GetType() const;
    [[nodiscard]] int GetStrength() const;
    [[nodiscard]] bool IsBroken() const;
    void Damage(int amount);
    void Repair();
    void CheckStrength() const;
};
}
