package station;

/** Действие над погибшим членом экипажа. */
public class DeadCrewException extends RuntimeException {
    public DeadCrewException(String name) {
        super("член экипажа погиб: " + name);
    }
}
