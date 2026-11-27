#pragma once

#include "BaseModule.hpp"

namespace station
{

// Жилой модуль: потребляет энергию пропорционально числу мест
class LivingModule : public BaseModule
{
private:
    int m_capacity{ 1 };

public:
    LivingModule();                                                  // по умолчанию
    LivingModule(std::string_view name, int strength,
                 std::shared_ptr<Dock> dock, int capacity);          // с параметрами

    // Пять операций: деструктор пишем сами (сообщение), остальные — по умолчанию
    LivingModule(const LivingModule& other) = default;
    LivingModule(LivingModule&& other) noexcept = default;
    LivingModule& operator=(const LivingModule& other) = default;
    LivingModule& operator=(LivingModule&& other) noexcept = default;
    ~LivingModule() noexcept override;

    [[nodiscard]] std::string GetKind() const; // скрывает BaseModule::GetKind (не override)
    [[nodiscard]] int GetPowerBalance() const override;
    [[nodiscard]] std::string Describe() const override; // с вызовом базового
    [[nodiscard]] std::unique_ptr<BaseModule> Clone() const override;

    [[nodiscard]] int GetCapacity() const;
};

} // namespace station
