public class Crew {
    public enum Role { ENGINEER, SCIENTIST, DOCTOR }
    public enum State { HEALTHY, WOUNDED, DEAD }

    private final String name;
    private final Role role;
    private State state;

    public Crew(String name, Role role) {
        this.name = name;
        this.role = role;
        this.state = State.HEALTHY;
        System.out.println("[Crew] Принят на станцию: " + name);
    }

    public void wound() {
        if (state == State.DEAD) {
            System.out.println("[Crew] Ошибка: мёртвого нельзя ранить повторно.");
            return;
        }
        state = State.WOUNDED;
        System.out.println("[Crew] " + name + " ранен.");
    }

    public void heal() {
        if (state == State.DEAD) {
            System.out.println("[Crew] Ошибка: мёртвого нельзя вылечить!");
            return;
        }
        state = State.HEALTHY;
        System.out.println("[Crew] " + name + " вылечен.");
    }

    public String getName() { return name; }
    public Role getRole() { return role; }
    public State getState() { return state; }

    @Override
    public String toString() {
        return name + " (" + role + ", " + state + ")";
    }
}
