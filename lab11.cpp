#include <iostream>
#include <concepts>

// Концепт для ограничения типов, пригодных для вычисления биномиальных коэффициентов
template<typename T>
concept BinomialApplicable = std::integral<T> && !std::same_as<T, bool>;

// Constexpr лямбда для вычисления биномиальных коэффициентов
template <BinomialApplicable T>
constexpr auto binomial = [](T n, T k) constexpr -> T {
    // Проверка корректности входных данных
    if (k < 0 || k > n) {
        return 0; // Неверные параметры
    }
    
    // Оптимизация: используем симметрию C(n, k) = C(n, n-k)
    if (k > n - k) {
        k = n - k;
    }
    
    // Вычисление биномиального коэффициента
    T result = 1;
    for (T i = 1; i <= k; ++i) {
        // Проверка на переполнение (опционально для constexpr)
        result *= (n - k + i);
        result /= i;
    }
    
    return result;
};

int main() {
    // Примеры вычислений во время компиляции
    constexpr auto c1 = binomial<int>(5, 2);    // C(5,2) = 10
    constexpr auto c2 = binomial<int>(10, 3);   // C(10,3) = 120
    constexpr auto c3 = binomial<int>(8, 4);    // C(8,4) = 70
    constexpr auto c4 = binomial<int>(7, 7);    // C(7,7) = 1
    constexpr auto c5 = binomial<int>(7, 0);    // C(7,0) = 1
    constexpr auto c6 = binomial<int>(5, 6);    // Неверные параметры -> 0
    
    std::cout << "C(5,2) = " << c1 << std::endl;
    std::cout << "C(10,3) = " << c2 << std::endl;
    std::cout << "C(8,4) = " << c3 << std::endl;
    std::cout << "C(7,7) = " << c4 << std::endl;
    std::cout << "C(7,0) = " << c5 << std::endl;
    std::cout << "C(5,6) (неверные параметры) = " << c6 << std::endl;
    
    // Дополнительные проверки в рантайме
    int n = 15, k = 5;
    auto runtime_result = binomial<int>(n, k);
    std::cout << "\nC(" << n << "," << k << ") = " << runtime_result << std::endl;
    
    // Проверка с использованием static_assert для compile-time вычислений
    static_assert(binomial<int>(6, 3) == 20);   // C(6,3) = 20
    static_assert(binomial<int>(10, 5) == 252); // C(10,5) = 252
    static_assert(binomial<int>(4, 2) == 6);    // C(4,2) = 6
    
    std::cout << "\nВсе compile-time проверки успешно пройдены!" << std::endl;
    
    return 0;
}
