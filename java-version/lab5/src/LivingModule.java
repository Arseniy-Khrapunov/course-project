package station;

/** Жилой модуль: потребляет энергию пропорционально числу мест. */
public class LivingModule extends BaseModule {
    private final int capacity;

    /** По умолчанию: this(...) передаёт работу конструктору с параметрами. */
    public LivingModule() {
        this("Без названия", 100, new Dock("-"), 1);
    }

    public LivingModule(String name, int strength, Dock dock, int capacity) {
        super("LIV", name, strength, dock); // конструктор базового класса — первой строкой
        this.capacity = capacity;
        System.out.println("  LivingModule(): " + name + ", мест " + capacity);
    }

    /** Конструктор копирования. */
    public LivingModule(LivingModule other) {
        super(other);
        this.capacity = other.capacity;
        System.out.println("  LivingModule(copy): " + other.getName());
    }

    /** Скрывает static-метод базы (не переопределяет). */
    public static String kindName() {
        return "жилой модуль";
    }

    @Override
    public int getPowerBalance() {
        return -5 * capacity;
    }

    /** Дополняет метод базового класса. */
    @Override
    public String describe() {
        return super.describe() + ", мест: " + capacity;
    }

    @Override
    public BaseModule copy() {
        return new LivingModule(this);
    }
}
