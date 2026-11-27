package station;

/** Интерфейс объекта поведения: как станция считает потребление энергии. */
public interface PowerPolicy {
    /** Сколько единиц энергии реально потребуется при базовом потреблении units. */
    int adjustedConsumption(int units);

    String getName();
}
