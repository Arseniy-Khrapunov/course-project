package station;

import java.util.ArrayList;
import java.util.List;

public class Station {
    private final String name;
    private final List<BaseModule> modules = new ArrayList<>(); // композиция
    private final List<Crew> crew = new ArrayList<>();          // агрегация
    private PowerPolicy policy; // объект поведения (конфигурирование)

    /** Статическое конфигурирование: политика задаётся при создании. */
    public Station(String name, PowerPolicy policy) {
        if (policy == null) {
            throw new EmptyObjectException("политика энергопотребления");
        }
        this.name = name;
        this.policy = policy;
        System.out.println("[Station] Станция " + name + " создана (режим: " + policy.getName() + ").");
    }

    /** Динамическое конфигурирование: политику можно заменить во время работы. */
    public void setPolicy(PowerPolicy policy) {
        if (policy == null) {
            throw new EmptyObjectException("политика энергопотребления"); // старая политика цела
        }
        this.policy = policy;
        System.out.println("[Station] Режим энергопотребления: " + policy.getName());
    }

    public void addModule(BaseModule module) {
        if (module == null) {
            throw new EmptyObjectException("модуль"); // раньше: сообщение и return
        }
        modules.add(module);
        System.out.println("[Station] Модуль " + module.getName() + " добавлен на станцию.");
    }

    public void addCrew(Crew c) {
        if (c == null) {
            throw new EmptyObjectException("член экипажа"); // раньше: сообщение и return
        }
        crew.add(c);
        System.out.println("[Station] " + c.getName() + " зачислен в экипаж.");
    }

    public int getTotalPower() {
        int production = 0;
        int consumption = 0;
        for (BaseModule m : modules) {
            int balance = m.getPowerBalance(); // позднее связывание
            if (balance > 0) {
                production += balance;
            } else {
                consumption += -balance;
            }
        }
        return production - policy.adjustedConsumption(consumption); // потребление считает объект поведения
    }

    /** Проверка типа: отключается только то, что реализует Switchable. */
    public void switchOffAll() {
        System.out.println("[Station] Аварийное отключение:");
        for (BaseModule m : modules) {
            if (m instanceof Switchable device) {
                device.switchOff();
            } else {
                System.out.println("  " + m.getName() + ": не отключается (нет Switchable)");
            }
        }
    }

    /** Сломанные модули пропускает; finally выполняется при любом исходе. */
    public void switchOnAll() {
        System.out.println("[Station] Запуск систем:");
        for (BaseModule m : modules) {
            if (m instanceof Switchable device) {
                try {
                    device.switchOn();
                } catch (ModuleBrokenException e) {
                    System.out.println("  пропущен (" + e.getMessage() + ")");
                } finally {
                    System.out.println("  [finally] попытка включения завершена: " + m.getName());
                }
            }
        }
    }

    public void report() {
        System.out.println("\n=== Станция " + name + " (режим: " + policy.getName() + ") ===");
        System.out.println("Модулей: " + modules.size());
        for (BaseModule m : modules) {
            System.out.println(" - " + m.describe());
        }
        System.out.println("Экипаж: " + crew.size());
        for (Crew c : crew) {
            System.out.println(" - " + c.getName());
        }
        System.out.println("Энергобаланс: " + getTotalPower());
        System.out.println("=====================");
    }

    public String getName() { return name; }
}
