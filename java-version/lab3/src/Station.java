import java.util.ArrayList;
import java.util.List;

public class Station {
    private final String name;
    private final List<Module> modules = new ArrayList<>(); // композиция
    private final List<Crew> crew = new ArrayList<>(); // агрегация

    public Station(String name) {
        this.name = name;
        System.out.println("[Station] Станция " + name + " создана.");
    }

    public void addModule(String moduleName, Module.Type type, int strength) {
        modules.add(new Module(moduleName, type, strength)); // целое создаёт часть само
        System.out.println("[Station] Модуль " + moduleName + " добавлен на станцию.");
    }

    public void addCrew(Crew c) { // экипаж создан снаружи
        if (c == null) {
            System.out.println("[Station] Ошибка: нельзя добавить пустого члена экипажа.");
            return;
        }
        crew.add(c);
        System.out.println("[Station] " + c.getName() + " зачислен в экипаж.");
    }

    public void report() {
        System.out.println("\n=== Станция " + name + " ===");
        System.out.println("Модулей: " + modules.size());
        for (Module m : modules) {
            System.out.println(" - " + m);
        }
        System.out.println("Экипаж: " + crew.size());
        for (Crew c : crew) {
            System.out.println(" - " + c.getName());
        }
        System.out.println("=====================\n");
    }

    public String getName() { return name; }
}
