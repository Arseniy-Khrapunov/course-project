package station;

/** Лаборатория: потребляет много энергии, ведёт журнал исследований. */
public class LabModule extends BaseModule {
    private final String field;
    private final ResearchLog log; // общий для копий: поверхностная копия

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
        this.log = other.log; // поверхностная копия: ссылка на тот же журнал
        System.out.println("  LabModule(copy): " + other.getName());
    }

    @Override
    public int getPowerBalance() {
        return -30;
    }

    /** Дополняет метод базового класса. */
    @Override
    public String describe() {
        String text = log.getText();
        return super.describe() + ", направление: " + field
                + ", журнал: " + (text.isEmpty() ? "пуст" : text);
    }

    @Override
    public BaseModule copy() {
        return new LabModule(this);
    }

    public void writeLog(String entry) {
        log.append(entry);
    }

    /** Один ли это журнал (а не просто одинаковый текст). */
    public boolean sharesLogWith(LabModule other) {
        return log == other.log;
    }
}
