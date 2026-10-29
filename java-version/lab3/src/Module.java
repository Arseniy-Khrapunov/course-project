// Лабораторная работа № 3. Java-версия.
public class Module {
    public enum Type { LIVING, LAB, REACTOR }

    private final String name;
    private final Type type;
    private int strength;
    private boolean broken;

    public Module(String name, Type type, int strength) {
        this.name = name;
        this.type = type;
        this.strength = strength;
        this.broken = false;
        System.out.println("[Module] Создан модуль: " + name);
        checkStrength();
    }

    public void damage(int amount) {
        strength -= amount;
        checkStrength();
        if (strength <= 0) {
            broken = true;
            System.out.println("[Module] Модуль " + name + " сломан!");
        }
    }

    public void repair() {
        strength = 100;
        broken = false;
        System.out.println("[Module] Модуль " + name + " отремонтирован.");
    }

    private void checkStrength() {
        if (strength < 0) {
            System.out.println("[Module] Ошибка: прочность не может быть отрицательной!");
        }
    }

    public String getName() { return name; }
    public Type getType() { return type; }
    public int getStrength() { return strength; }
    public boolean isBroken() { return broken; }

    @Override
    public String toString() {
        return name + " (прочность: " + strength + (broken ? ", СЛОМАН" : ", активен") + ")";
    }
}
