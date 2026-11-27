package station;

/** Интерфейс: «устройство можно включать и отключать». Без префикса I — так принято в Java. */
public interface Switchable {
    void switchOn() throws ModuleBrokenException;

    void switchOff();

    boolean isOn();
}
