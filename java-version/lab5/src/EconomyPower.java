package station;

/** Экономный режим: потребление снижено до 60 %. */
public final class EconomyPower implements PowerPolicy {
    private static final int PERCENT = 60;

    @Override
    public int adjustedConsumption(int units) {
        return units * PERCENT / 100;
    }

    @Override
    public String getName() {
        return "экономный";
    }
}
