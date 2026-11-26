package station;

/** Журнал исследований лаборатории. */
public class ResearchLog {
    private String text = "";

    public void append(String entry) {
        if (!text.isEmpty()) {
            text += "; ";
        }
        text += entry;
    }

    public String getText() {
        return text;
    }
}
