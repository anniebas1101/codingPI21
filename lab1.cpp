#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

// Определение структуры (для первого способа)
struct Goods {
    double first;  //цена товара (дробное положительное число)
    int second;    //количество единиц товара (целое положительное число)

    // Метод инициализации с контролем корректности
    void init(double f, int s) {
        if (f <= 0 || s <= 0) {
            cout << "Ошибка: цена и количество должны быть положительными числами!" << endl;
            first = 0;
            second = 0;
        } else {
            first = f;
            second = s;
        }
    }

    // Метод ввода с клавиатуры
    void read() {
        cout << "Введите цену товара (положительное число): ";
        cin >> first;
        cout << "Введите количество единиц товара (целое положительное число): ";
        cin >> second;

        if (first <= 0 || second <= 0) {
            cout << "Ошибка: значения должны быть положительными!" << endl;
            first = 0;
            second = 0;
        }
    }

    // Метод вывода на экран
    void display() {
        cout << "Цена товара: " << first << " руб." << endl;
        cout << "Количество единиц: " << second << " шт." << endl;
    }

    // Метод вычисления стоимости товара
    double cost() {
        return first * second;
    }
};

// Внешняя функция make_goods() для создания структуры
Goods make_goods(double f, int s) {
    Goods g;

    if (f <= 0 || s <= 0) {
        cout << "Ошибка: цена и количество должны быть положительными числами!" << endl;
        exit(1);  // Завершение программы при ошибочных параметрах
    }

    g.init(f, s);
    return g;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Лабораторная работа №1, задание 5 ===" << endl;
    cout << "Структура Goods (цена товара, количество единиц)" << endl << endl;

    // Способ 1: создание объекта и инициализация через метод init()
    cout << "--- Способ 1: создание объекта и инициализация через init() ---" << endl;
    Goods product1;
    product1.init(150.50, 3);
    product1.display();
    cout << "Стоимость товара: " << product1.cost() << " руб." << endl << endl;

    // Способ 2: создание объекта и ввод с клавиатуры
    Goods product2;
    product2.read();
    cout << endl;
    product2.display();
    cout << "Стоимость товара: " << product2.cost() << " руб." << endl << endl;

    // Способ 3: создание объекта через внешнюю функцию make_goods()
    Goods product3 = make_goods(299.99, 5);
    product3.display();
    cout << "Стоимость товара: " << product3.cost() << " руб." << endl << endl;

    // Способ 4: массив объектов
    const int ARRAY_SIZE = 3;
    Goods products[ARRAY_SIZE];

    // Инициализация элементов массива
    products[0].init(50.75, 2);
    products[1].init(120.30, 1);
    products[2].init(89.90, 4);

    // Вывод информации о всех товарах в массиве
    double totalCost = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << "Товар " << i + 1 << ":" << endl;
        products[i].display();
        double cost = products[i].cost();
        cout << "Стоимость: " << cost << " руб." << endl << endl;
        totalCost += cost;
    }
    cout << "Общая стоимость всех товаров: " << totalCost << " руб." << endl << endl;

    // Способ 5: динамическое создание объекта
    Goods* dynamicProduct = new Goods;
    dynamicProduct->init(450.25, 2);
    dynamicProduct->display();
    cout << "Стоимость товара: " << dynamicProduct->cost() << " руб." << endl;

    // Освобождение памяти
    delete dynamicProduct;

    cin.get();

    return 0;
}
