package station;

/** Передан null там, где объект обязателен. */
public class EmptyObjectException extends RuntimeException {
    public EmptyObjectException(String what) {
        super("пустой объект: " + what);
    }
}
