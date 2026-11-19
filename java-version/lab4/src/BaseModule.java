package station;

import java.util.Objects;

/** Абстрактный базовый класс модуля станции. */
public abstract class BaseModule {
    private static int lastNumber = 0; // статическое поле: счётчик инвентарных номеров

    private final int inventoryNumber;
    private final String serial;
    private final String name;
    private int strength;
    private boolean broken;
    private Dock dock;

    /** Конструктор с параметрами. protected: создавать объект могут только наследники. */
    protected BaseModule(String prefix, String name, int strength, Dock dock) {
        this.inventoryNumber = nextInventoryNumber();
        this.serial = makeSerial(prefix, inventoryNumber);
        this.name = name;
        this.strength = strength;
        this.broken = false;
        this.dock = dock;
        System.out.println("  BaseModule(): " + name + " [" + serial + "]");
        checkStrength();
    }

    /** Конструктор копирования: глубокое копирование узла, новый инвентарный номер. */
    protected BaseModule(BaseModule other) {
        this.inventoryNumber = nextInventoryNumber();
        this.serial = makeSerial(other.getSerialPrefix(), inventoryNumber);
        this.name = other.name;
        this.strength = other.strength;
        this.broken = other.broken;
        this.dock = other.dock == null ? null : new Dock(other.dock);
        System.out.println("  BaseModule(copy): " + name + " [" + serial + "]");
    }

    public static int nextInventoryNumber() {
        return ++lastNumber;
    }

    public static int getCreatedCount() {
        return lastNumber;
    }

    private static String makeSerial(String prefix, int number) {
        String digits = String.valueOf(number);
        while (digits.length() < 3) {
            digits = "0" + digits;
        }
        return prefix + "-" + digits;
    }

    private void checkStrength() {
        if (strength < 0) {
            System.out.println("[Module] Ошибка: прочность не может быть отрицательной!");
        }
    }

    // Абстрактные методы: у каждого наследника своя реализация
    public abstract int getPowerBalance();

    public abstract BaseModule copy();

    /** Есть реализация, наследник может дополнить или заменить её. */
    public String describe() {
        return header() + ", прочность " + strength + (broken ? ", СЛОМАН" : ", активен");
    }

    /** Общая часть описания: нужна наследникам и классам пакета station. */
    protected String header() {
        return name + " [" + serial + ", узел " + (dock == null ? "-" : dock.getCode()) + "]";
    }

    public String getName() {
        return name;
    }

    public String getSerial() {
        return serial;
    }

    public int getStrength() {
        return strength;
    }

    public boolean isBroken() {
        return broken;
    }

    public String getDockCode() {
        return dock == null ? "-" : dock.getCode();
    }

    public String getSerialPrefix() {
        return serial.substring(0, serial.indexOf('-'));
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

    public void renameDock(String code) {
        if (dock != null) {
            dock.setCode(code);
        }
    }

    /** Передаём текущий объект (this) другому объекту. */
    public void putOnDock(Dock target) {
        target.register(this);
    }

    /** Модули равны, если совпадают вид и название (а не ссылка). */
    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        BaseModule other = (BaseModule) o;
        return name.equals(other.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(getClass().getName(), name);
    }

    @Override
    public String toString() {
        return describe();
    }
}
