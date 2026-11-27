package station;

/** Прочность модуля задана отрицательной. */
public class InvalidStrengthException extends RuntimeException {
    public InvalidStrengthException(int value) {
        super("прочность не может быть отрицательной: " + value);
    }
}
