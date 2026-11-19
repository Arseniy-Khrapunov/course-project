package station;

/** Стыковочный узел, к которому подключён модуль. */
public class Dock {
    private String code;

    public Dock(String code) {
        this.code = code; // this различает поле и параметр
    }

    /** Конструктор копирования: this(...) вызывает другой конструктор этого же класса. */
    public Dock(Dock other) {
        this(other.code);
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    /** Принимает модуль на узел. */
    public void register(BaseModule module) {
        System.out.println("[Dock] Узел " + code + ": принят модуль " + module.getSerial());
    }
}
