import java.util.Arrays;

import station.BaseModule;
import station.BoostPower;
import station.Crew;
import station.DeadCrewException;
import station.Dock;
import station.EconomyPower;
import station.EmptyObjectException;
import station.InvalidDamageException;
import station.InvalidStrengthException;
import station.LabModule;
import station.LivingModule;
import station.ModuleBrokenException;
import station.ReactorModule;
import station.StandardPower;
import station.Station;
import station.Switchable;

public class Main {
    public static void main(String[] args) {
        System.out.println("===== ЛР 5. Java-версия =====");

        LabModule lab = new LabModule("Лаборатория", 90, new Dock("B-2"), "биология");
        ReactorModule reactor = new ReactorModule("Реактор-1", 100, new Dock("R-1"), 120);
        LivingModule living = new LivingModule("Жилой отсек", 100, new Dock("A-1"), 4);

        System.out.println("\n--- 1. Интерфейс Switchable ---");
        emergencyShutdown(lab);
        emergencyShutdown(reactor);
        System.out.println("lab.isOn(): " + lab.isOn() + ", reactor.isOn(): " + reactor.isOn());

        System.out.println("\n--- 2. extends + implements ---");
        BaseModule asModule = lab;
        Switchable asDevice = lab;
        System.out.println("Как BaseModule: " + asModule.getName() + " [" + asModule.getSerial() + "]");
        System.out.println("Как Switchable: включена = " + asDevice.isOn());

        System.out.println("\n--- 3. Раннее и позднее связывание ---");
        try {
            lab.switchOn();
        } catch (ModuleBrokenException e) {
            System.out.println("  Не удалось включить: " + e.getMessage());
        }
        System.out.println("LabModule.kindName():            " + LabModule.kindName());
        System.out.println("asModule.kindName() (BaseModule): " + asModule.kindName()
                + "   <- раннее: static, по типу переменной");
        System.out.println("asModule.describe():\n  " + asModule.describe()
                + "\n   ^ позднее: обычный метод, по настоящему типу объекта");

        System.out.println("\n--- 4. instanceof и Comparable ---");
        trySwitchOff(living);
        trySwitchOff(lab);
        BaseModule[] modules = { reactor, living, lab };
        Arrays.sort(modules); // сортировка знает только о Comparable
        System.out.print("Модули по названию:");
        for (BaseModule m : modules) {
            System.out.print(" " + m.getName() + ";");
        }
        System.out.println();

        System.out.println("\n--- 5. Конфигурирование станции ---");
        Station station = new Station("МКС-1", new StandardPower()); // статически
        station.addModule(new ReactorModule("Реактор-2", 100, new Dock("R-2"), 120));
        ReactorModule spare = new ReactorModule("Резервный реактор", 100, new Dock("R-3"), 80);
        spare.damage(100); // сломан
        station.addModule(spare);
        station.addModule(new LivingModule("Жилой отсек-2", 100, new Dock("A-2"), 4));
        station.addModule(new LabModule("Лаборатория-2", 95, new Dock("B-3"), "химия"));
        station.report();
        station.setPolicy(new EconomyPower()); // динамически
        System.out.println("Энергобаланс: " + station.getTotalPower());
        station.setPolicy(new BoostPower());
        System.out.println("Энергобаланс: " + station.getTotalPower());
        station.setPolicy(new StandardPower());
        station.switchOffAll();
        System.out.println("Энергобаланс после отключения: " + station.getTotalPower());
        station.switchOnAll();
        System.out.println("Энергобаланс после запуска: " + station.getTotalPower());

        System.out.println("\n--- 6. Исключения ---");
        System.out.println("[6.1 нарушение правила при создании]");
        try {
            new LabModule("Брак", -10, new Dock("T-2"), "химия");
            System.out.println("  сюда управление не дойдёт");
        } catch (InvalidStrengthException e) {
            System.out.println("  Перехвачено нарушение правила: " + e.getMessage());
            System.out.println("  Выдано номеров: " + BaseModule.getCreatedCount()
                    + " (номер неудавшегося модуля не потрачен)");
        }

        System.out.println("[6.2 отрицательный урон]");
        try {
            living.damage(20);
            System.out.println("  урон 20 нанесён, прочность " + living.getStrength());
            living.damage(-5);
        } catch (InvalidDamageException e) {
            System.out.println("  Перехвачено нарушение правила: " + e.getMessage());
        }

        System.out.println("[6.3 сломанный реактор: перехват, ремонт и повтор, finally]");
        reactor.damage(100);
        switchOnWithRepair(reactor);

        System.out.println("[6.4 пустой модуль]");
        try {
            station.addModule(null);
        } catch (EmptyObjectException e) {
            System.out.println("  Перехвачено нарушение правила: " + e.getMessage());
        }

        System.out.println("[6.5 погибший член экипажа]");
        Crew engineer = new Crew("Иванов", Crew.Role.ENGINEER);
        station.addCrew(engineer);
        try {
            engineer.wound();
            engineer.heal();
            engineer.kill();
            engineer.heal();
        } catch (DeadCrewException e) {
            System.out.println("  Перехвачено нарушение правила: " + e.getMessage());
        }

        System.out.println("\n===== Конец демонстрации =====");
    }

    /** Работает через интерфейс и не знает, какой именно класс перед ней. */
    private static void emergencyShutdown(Switchable device) {
        if (device.isOn()) {
            device.switchOff();
        }
    }

    /** Проверка типа: отключить можно только то, что реализует Switchable. */
    private static void trySwitchOff(BaseModule module) {
        if (module instanceof Switchable device) {
            device.switchOff();
        } else {
            System.out.println("  " + module.getName() + ": отключить нельзя — не реализует Switchable");
        }
    }

    /** Исключение перехватывается там, где понятно, что делать: починить и повторить. */
    private static void switchOnWithRepair(BaseModule module) {
        if (!(module instanceof Switchable device)) {
            return;
        }
        try {
            device.switchOn();
        } catch (ModuleBrokenException e) {
            System.out.println("  Ошибка: " + e.getMessage() + " — ремонтируем и повторяем");
            module.repair();
            try {
                device.switchOn();
            } catch (ModuleBrokenException again) {
                System.out.println("  Не удалось и после ремонта: " + again.getMessage());
            }
        } finally {
            System.out.println("  [finally] попытка включения завершена: " + module.getName());
        }
    }
}
