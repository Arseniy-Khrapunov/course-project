package station;

/** Лаборатория: extends BaseModule (состояние) implements Switchable (контракт). */
public class LabModule extends BaseModule implements Switchable {
    private final String field;
    private final ResearchLog log; // общий для копий: поверхностная копия
    private boolean online = true;

    public LabModule(String name, int strength, Dock dock, String field) {
        super("LAB", name, strength, dock);
        this.field = field;
        this.log = new ResearchLog();
        System.out.println("  LabModule(): " + name + ", направление " + field);
    }

    /** Конструктор копирования: узел копируется глубоко (в базе), журнал — общий. */
    public LabModule(LabModule other) {
        super(other);
        this.field = other.field;
        this.log = other.log; // поверхностная копия
        this.online = other.online;
        System.out.println("  LabModule(copy): " + other.getName());
    }

    /** Скрывает static-метод базы (не переопределяет). */
    public static String kindName() {
        return "лаборатория";
    }

    @Override
    public int getPowerBalance() {
        return online ? -30 : 0;
    }

    @Override
    public String describe() {
        String text = log.getText();
        return super.describe() + ", направление: " + field
                + (online ? ", включена" : ", отключена")
                + ", журнал: " + (text.isEmpty() ? "пуст" : text);
    }

    @Override
    public BaseModule copy() {
        return new LabModule(this);
    }

    @Override
    public void switchOn() throws ModuleBrokenException {
        if (isBroken()) { // проверка до изменения состояния
            throw new ModuleBrokenException(getName());
        }
        online = true;
        System.out.println("  [Lab] " + getName() + ": включена");
    }

    @Override
    public void switchOff() {
        online = false;
        System.out.println("  [Lab] " + getName() + ": отключена");
    }

    @Override
    public boolean isOn() {
        return online;
    }

    public void writeLog(String entry) {
        log.append(entry);
    }

    /** Один ли это журнал (а не просто одинаковый текст). */
    public boolean sharesLogWith(LabModule other) {
        return log == other.log;
    }
}
