package station;

/** Форсированный режим: потребление вырастает до 150 %. */
public final class BoostPower implements PowerPolicy {
    private static final int PERCENT = 150;

    @Override
    public int adjustedConsumption(int units) {
        return units * PERCENT / 100;
    }

    @Override
    public String getName() {
        return "форсированный";
    }
}
