package station;

import java.util.ArrayList;
import java.util.List;

public class Station {
    private final String name;
    private final List<BaseModule> modules = new ArrayList<>(); // композиция
    private final List<Crew> crew = new ArrayList<>();          // агрегация

    public Station(String name) {
        this.name = name;
        System.out.println("[Station] Станция " + name + " создана.");
    }

    /** Станция становится единственным владельцем модуля любого вида. */
    public void addModule(BaseModule module) {
        if (module == null) {
            System.out.println("[Station] Ошибка: нельзя добавить пустой модуль.");
            return;
        }
        modules.add(module);
        System.out.println("[Station] Модуль " + module.getName() + " добавлен на станцию.");
    }

    public void addCrew(Crew c) { // экипаж создан снаружи
        if (c == null) {
            System.out.println("[Station] Ошибка: нельзя добавить пустого члена экипажа.");
            return;
        }
        crew.add(c);
        System.out.println("[Station] " + c.getName() + " зачислен в экипаж.");
    }

    public int getTotalPower() {
        int total = 0;
        for (BaseModule m : modules) {
            total += m.getPowerBalance(); // полиморфный вызов
        }
        return total;
    }

    public void report() {
        System.out.println("\n=== Станция " + name + " ===");
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
