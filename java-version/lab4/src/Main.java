import java.util.HashSet;
import java.util.Set;

import station.BaseModule;
import station.Crew;
import station.Dock;
import station.LabModule;
import station.LivingModule;
import station.ReactorModule;
import station.Station;

public class Main {
    public static void main(String[] args) {
        System.out.println("===== ЛР 4. Java-версия =====");

        System.out.println("\n--- 1. Конструкторы и порядок вызовов ---");
        System.out.println("[жилой модуль с параметрами]");
        LivingModule living = new LivingModule("Жилой отсек", 100, new Dock("A-1"), 4);
        System.out.println("[жилой модуль по умолчанию: this(...)]");
        LivingModule empty = new LivingModule();
        // new BaseModule(...);  // ошибка компиляции: BaseModule — абстрактный класс

        System.out.println("\n--- 2. Массив BaseModule[] ---");
        BaseModule[] modules = {
            new LivingModule("Жилой отсек-2", 100, new Dock("A-2"), 6),
            new LabModule("Лаборатория", 90, new Dock("B-5"), "физика"),
            new ReactorModule("Реактор-1", 100, new Dock("R-1"), 80)
        };
        int total = 0;
        for (BaseModule module : modules) {
            System.out.println(" - " + module.describe() + "; энергия " + module.getPowerBalance());
            total += module.getPowerBalance();
        }
        System.out.println("Итого энергобаланс: " + total);
        // modules[0].header();  // ошибка компиляции: header() — protected, Main вне пакета station

        System.out.println("\n--- 3. Глубокая и поверхностная копия ---");
        System.out.println("[копируем жилой модуль]");
        LivingModule copy = new LivingModule(living);
        copy.renameDock("Z-9");
        System.out.println("original: " + living.describe());
        System.out.println("copy:     " + copy.describe());
        System.out.println("Узел оригинала остался " + living.getDockCode() + " (глубокая копия)");

        LabModule lab = new LabModule("Лаборатория-2", 95, new Dock("C-3"), "химия");
        System.out.println("[копируем лабораторию]");
        LabModule labCopy = new LabModule(lab);
        labCopy.writeLog("опыт №1");
        System.out.println("lab:      " + lab.describe());
        System.out.println("Журнал общий: " + lab.sharesLogWith(labCopy) + " (поверхностная копия)");

        System.out.println("\n--- 4. Копирование через ссылку на базовый класс: copy() ---");
        BaseModule twin = modules[1].copy();
        System.out.println("twin: " + twin.describe());

        System.out.println("\n--- 5. Сравнение по содержимому: equals и hashCode ---");
        System.out.println("lab == labCopy:      " + (lab == labCopy));
        System.out.println("lab.equals(labCopy): " + lab.equals(labCopy));
        System.out.println("hashCode равны:      " + (lab.hashCode() == labCopy.hashCode()));
        System.out.println("lab.equals(living):  " + lab.equals(living));
        Set<BaseModule> set = new HashSet<>();
        set.add(lab);
        set.add(labCopy);
        System.out.println("В HashSet после добавления lab и labCopy: " + set.size() + " элемент");

        System.out.println("\n--- 6. Станция и переопределённые методы ---");
        Station station = new Station("МКС-1");
        station.addModule(modules[0]);
        station.addModule(modules[1]);
        station.addModule(modules[2].copy());
        station.addModule(null); // проверка правила
        station.addCrew(new Crew("Иванов", Crew.Role.ENGINEER));
        station.report();
        modules[2].damage(100);
        System.out.println(modules[2].describe());

        System.out.println("\n--- 7. this: передача текущего объекта ---");
        Dock dock = new Dock("D-4");
        living.putOnDock(dock);

        System.out.println("\n--- 8. Статические члены ---");
        System.out.println("Создано модулей (BaseModule.getCreatedCount()): "
                + BaseModule.getCreatedCount());

        System.out.println("\n===== Конец демонстрации =====");
    }
}
