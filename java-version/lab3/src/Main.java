import java.lang.ref.WeakReference;

public class Main {
    public static void main(String[] args) {
        System.out.println("===== ЛР 3. Java-версия =====\n");

        System.out.println("--- Часть 1: Ссылки и копии ---");
        Crew engineer = new Crew("Иванов", Crew.Role.ENGINEER);
        Crew sameEngineer = engineer;   // копия ссылки, а не объекта
        sameEngineer.wound();
        System.out.println("Проверка: engineer ранен? " +
                (engineer.getState() == Crew.State.WOUNDED));
        System.out.println("Сравнение ссылок (один объект): " +
                (engineer == sameEngineer)); // true

        System.out.println("\n--- Часть 2: Освобождение ресурса ---");
        try (IssueLog log = new IssueLog("Журнал станции")) {
            log.write("Запуск систем жизнеобеспечения");
            log.write("Экипаж занял жилой модуль");
        } // здесь гарантированно вызван close()

        System.out.println("\n--- Часть 3: Сборщик мусора ---");
        Crew temp = new Crew("Временный", Crew.Role.DOCTOR);
        WeakReference<Crew> watcher = new WeakReference<>(temp);
        System.out.println("Объект жив? " + (watcher.get() != null));
        temp = null;
        System.gc();
        try { Thread.sleep(100); } catch (InterruptedException e) {}
        System.out.println("После gc(): объект жив? " +
                (watcher.get() != null));

        System.out.println("\n--- Часть 4: Станция с модулями и экипажем ---");
        {
            Station station = new Station("МКС-1");
            station.addModule("Жилой отсек", Module.Type.LIVING, 100);
            station.addModule("Реактор", Module.Type.REACTOR, 100);
            station.addCrew(engineer);
            station.addCrew(new Crew("Петрова", Crew.Role.DOCTOR));
            station.report();
        }
        System.gc();
        System.out.println("После выхода из блока и gc()...");
    }
}
