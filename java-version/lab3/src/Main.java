import java.lang.ref.WeakReference;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("===== ЛР 3. Java-версия =====\n");

        System.out.println("--- 1. Ссылки и копии ---");
        Crew engineer = new Crew("Иванов", Crew.Role.ENGINEER);
        Crew sameEngineer = engineer; // копия ссылки, а не объекта
        sameEngineer.wound();
        System.out.println("engineer ранен? " + (engineer.getState() == Crew.State.WOUNDED));
        System.out.println("engineer == sameEngineer: " + (engineer == sameEngineer));

        System.out.println("\n--- 2. Освобождение ресурса ---");
        try (IssueLog log = new IssueLog("Журнал станции")) {
            log.write("Запуск систем жизнеобеспечения");
            log.write("Экипаж занял жилой модуль");
        } // здесь гарантированно вызван close()
        System.out.println("(блок try закончился)");

        System.out.println("\n--- 3. Композиция, агрегация, проверка правил ---");
        Crew doctor = new Crew("Петрова", Crew.Role.DOCTOR); // создан снаружи
        WeakReference<Station> stationWatcher = buildStation(engineer, doctor);
        System.out.println("Блок закончился. Станция жива? " + (stationWatcher.get() != null));
        System.gc();
        Thread.sleep(100);
        System.out.println("После gc(): станция жива? " + (stationWatcher.get() != null));
        System.out.println("Экипаж после станции: " + engineer + ", " + doctor);

        System.out.println("\n--- 4. Сборщик мусора для одиночного объекта ---");
        Crew temp = new Crew("Временный", Crew.Role.SCIENTIST);
        WeakReference<Crew> watcher = new WeakReference<>(temp);
        System.out.println("Объект жив? " + (watcher.get() != null));
        temp = null;
        System.gc();
        Thread.sleep(100);
        System.out.println("После gc(): объект жив? " + (watcher.get() != null));
    }

    // Отдельный метод: после возврата локальных ссылок на станцию не остаётся
    private static WeakReference<Station> buildStation(Crew first, Crew second) {
        Station station = new Station("МКС-1");
        station.addModule("Жилой отсек", Module.Type.LIVING, 100);
        station.addModule("Реактор", Module.Type.REACTOR, 100);
        station.addCrew(first);
        station.addCrew(second);
        station.addCrew(null); // проверка правила: пустого члена экипажа нельзя
        station.report();

        Module probe = new Module("Пробный", Module.Type.LAB, 50);
        probe.damage(80); // проверка правила: прочность ушла в минус
        return new WeakReference<>(station);
    }
}
