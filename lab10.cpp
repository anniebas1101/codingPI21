#include <iostream>
#include <type_traits>

// Версия 1: До C++17 (рекурсивная реализация)
namespace pre_cpp17 {
    // Базовый случай рекурсии - один аргумент
    template<typename Condition>
    bool allTrue(Condition&& cond) {
        return static_cast<bool>(std::forward<Condition>(cond));
    }

    // Рекурсивный случай - несколько аргументов
    template<typename First, typename... Rest>
    bool allTrue(First&& first, Rest&&... rest) {
        return static_cast<bool>(std::forward<First>(first)) 
               && allTrue(std::forward<Rest>(rest)...);
    }
}

// Версия 2: C++17 и новее (с использованием fold expression)
namespace cpp17_and_later {
    template<typename... Conditions>
    bool allTrue(Conditions&&... conditions) {
        // Используем fold expression с оператором &&
        // Выражение развернется в: (cond1 && cond2 && ... && condN)
        return (static_cast<bool>(std::forward<Conditions>(conditions)) && ...);
    }
}

// Демонстрационная функция
int main() {
    std::cout << "=== Тестирование функции allTrue (до C++17) ===\n";
    
    // Все условия истинны
    std::cout << "pre_cpp17::allTrue(true, 1, 3.14, \"hello\") = " << std::boolalpha << pre_cpp17::allTrue(true, 1, 3.14, "hello") << std::endl;  // true
    
    // Одно условие ложно
    std::cout << "pre_cpp17::allTrue(true, 0, 3.14, \"hello\") = " << pre_cpp17::allTrue(true, 0, 3.14, "hello") << std::endl;  // false (0 преобразуется в false)
    
    // Пустой вызов не поддерживается в рекурсивной версии
    std::cout << "\n=== Тестирование функции allTrue (C++17 и новее) ===\n";
    
    // Все условия истинны
    std::cout << "cpp17_and_later::allTrue(true, 1, 3.14, \"hello\") = " << cpp17_and_later::allTrue(true, 1, 3.14, "hello") << std::endl;  // true
    
    // Одно условие ложно
    std::cout << "cpp17_and_later::allTrue(true, 0, 3.14, \"hello\") = " << cpp17_and_later::allTrue(true, 0, 3.14, "hello") << std::endl;  // false
    
    // Пустой вызов (всегда true для пустого пакета параметров)
    std::cout << "cpp17_and_later::allTrue() = " << cpp17_and_later::allTrue() << std::endl;  // true (пустой пакет считается истинным)
    
    // С различными типами, которые могут быть преобразованы в bool
    std::cout << "cpp17_and_later::allTrue(5 > 3, 10, 'a', nullptr) = " << cpp17_and_later::allTrue(5 > 3, 10, 'a', nullptr) << std::endl;  // false (nullptr преобразуется в false)
    
    return 0;
}
