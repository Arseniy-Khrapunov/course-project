package station;

/** Обычный режим: потребление без изменений. */
public final class StandardPower implements PowerPolicy {
    @Override
    public int adjustedConsumption(int units) {
        return units;
    }

    @Override
    public String getName() {
        return "стандартный";
    }
}
