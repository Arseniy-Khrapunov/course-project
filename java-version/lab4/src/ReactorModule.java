package station;

/** Реактор: единственный источник энергии. final — от него не наследуются. */
public final class ReactorModule extends BaseModule {
    private final int output;

    public ReactorModule(String name, int strength, Dock dock, int output) {
        super("REA", name, strength, dock);
        this.output = output;
        System.out.println("  ReactorModule(): " + name + ", мощность " + output);
    }

    public ReactorModule(ReactorModule other) {
        super(other);
        this.output = other.output;
        System.out.println("  ReactorModule(copy): " + other.getName());
    }

    /** Сломанный реактор энергию не выдаёт. */
    @Override
    public int getPowerBalance() {
        return isBroken() ? 0 : output;
    }

    /** Заменяет метод базового класса полностью: super.describe() не вызывается. */
    @Override
    public String describe() {
        return "Реактор " + header() + ", выдаёт " + getPowerBalance();
    }

    @Override
    public BaseModule copy() {
        return new ReactorModule(this);
    }
}
