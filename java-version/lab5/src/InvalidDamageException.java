package station;

/** Урон задан отрицательным числом. */
public class InvalidDamageException extends RuntimeException {
    public InvalidDamageException(int value) {
        super("урон не может быть отрицательным: " + value);
    }
}
