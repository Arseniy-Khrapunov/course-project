package station;

/** Реактор: единственный источник энергии. final — от него не наследуются. */
public final class ReactorModule extends BaseModule implements Switchable {
    private final int output;
    private boolean online = true;

    public ReactorModule(String name, int strength, Dock dock, int output) {
        super("REA", name, strength, dock);
        this.output = output;
        System.out.println("  ReactorModule(): " + name + ", мощность " + output);
    }

    public ReactorModule(ReactorModule other) {
        super(other);
        this.output = other.output;
        this.online = other.online;
        System.out.println("  ReactorModule(copy): " + other.getName());
    }

    /** Скрывает static-метод базы (не переопределяет). */
    public static String kindName() {
        return "реактор";
    }

    /** Сломанный или остановленный реактор энергию не выдаёт. */
    @Override
    public int getPowerBalance() {
        return (isBroken() || !online) ? 0 : output;
    }

    /** Заменяет метод базового класса полностью: super.describe() не вызывается. */
    @Override
    public String describe() {
        return "Реактор " + header() + (online ? ", в работе" : ", остановлен")
                + ", выдаёт " + getPowerBalance();
    }

    @Override
    public BaseModule copy() {
        return new ReactorModule(this);
    }

    @Override
    public void switchOn() throws ModuleBrokenException {
        if (isBroken()) {
            throw new ModuleBrokenException(getName());
        }
        online = true;
        System.out.println("  [Reactor] " + getName() + ": запущен");
    }

    @Override
    public void switchOff() {
        online = false;
        System.out.println("  [Reactor] " + getName() + ": остановлен");
    }

    @Override
    public boolean isOn() {
        return online;
    }
}
