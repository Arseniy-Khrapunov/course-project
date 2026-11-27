package station;

/**
 * Действие над сломанным модулем. Проверяемое исключение (наследник Exception):
 * компилятор требует перехватить его или объявить в throws.
 */
public class ModuleBrokenException extends Exception {
    public ModuleBrokenException(String name) {
        super("модуль сломан: " + name);
    }
}
