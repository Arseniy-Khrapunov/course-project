#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

namespace station
{

// Прочность модуля задана отрицательной (нарушение, которого в правильной программе быть не должно)
class InvalidStrengthError : public std::logic_error
{
public:
    explicit InvalidStrengthError(int value)
        : std::logic_error{ "прочность не может быть отрицательной: " + std::to_string(value) }
    {}
};

// Урон задан отрицательным числом
class InvalidDamageError : public std::logic_error
{
public:
    explicit InvalidDamageError(int value)
        : std::logic_error{ "урон не может быть отрицательным: " + std::to_string(value) }
    {}
};

// Передан пустой объект там, где он обязателен
class EmptyObjectError : public std::logic_error
{
public:
    explicit EmptyObjectError(std::string_view what)
        : std::logic_error{ "пустой объект: " + std::string(what) }
    {}
};

// Действие над сломанным модулем (ошибка времени выполнения)
class ModuleBrokenError : public std::runtime_error
{
public:
    explicit ModuleBrokenError(std::string_view name)
        : std::runtime_error{ "модуль сломан: " + std::string(name) }
    {}
};

// Действие над погибшим членом экипажа (ошибка времени выполнения)
class DeadCrewError : public std::runtime_error
{
public:
    explicit DeadCrewError(std::string_view name)
        : std::runtime_error{ "член экипажа погиб: " + std::string(name) }
    {}
};

} // namespace station
