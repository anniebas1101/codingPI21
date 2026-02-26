#include <iostream>

// Шаблонная функция для вырезки подмассива из массива
template <typename T>
T* extractSubarray(const T* source, int sourceSize, int startIndex, int length) {
    // Проверка корректности индексов
    if (startIndex < 0 || startIndex >= sourceSize || length <= 0) {
        return nullptr; // Некорректные параметры
    }

    // Определяем реальную длину подмассива (не выходим за границы)
    int actualLength = length;
    if (startIndex + length > sourceSize) {
        actualLength = sourceSize - startIndex;
    }

    // Выделяем память под новый массив
    T* subarray = new T[actualLength];

    // Копируем элементы
    for (int i = 0; i < actualLength; ++i) {
        subarray[i] = source[startIndex + i];
    }

    return subarray;
}

// Вспомогательная функция для вывода массива
template <typename T>
void printArray(const T* arr, int size) {
    std::cout << "[";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]";
}

// Пример использования
int main() {
    // Исходный массив
    int source[] = {10, 20, 30, 40, 50, 60, 70};
    int sourceSize = sizeof(source) / sizeof(source[0]);

    std::cout << "Исходный массив: ";
    printArray(source, sourceSize);
    std::cout << std::endl;

    // Вырезаем подмассив: начиная с индекса 2, длиной 4
    int start = 2;
    int len = 4;
    int* sub = extractSubarray(source, sourceSize, start, len);

    if (sub != nullptr) {
        std::cout << "Подмассив (start=" << start << ", length=" << len << "): ";
        printArray(sub, (start + len > sourceSize ? sourceSize - start : len));
        std::cout << std::endl;

        // Освобождаем память
        delete[] sub;
    } else {
        std::cout << "Ошибка: некорректные параметры" << std::endl;
    }

    return 0;
}
