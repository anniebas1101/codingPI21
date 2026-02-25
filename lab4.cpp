#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

class Triangle {
private:
    double sideA, sideB, sideC; // стороны треугольника
    double angleA, angleB, angleC; // углы в градусах

    // Приватный метод для проверки существования треугольника
    bool exists() const {
        // Проверка неравенства треугольника
        if (sideA + sideB <= sideC || sideA + sideC <= sideB || sideB + sideC <= sideA)
            return false;
        
        // Проверка суммы углов (должна быть 180 градусов)
        const double eps = 1e-6;
        if (fabs(angleA + angleB + angleC - 180.0) > eps)
            return false;
        
        // Проверка соответствия сторон и углов (теорема синусов)
        double sinA = sin(angleA * M_PI / 180.0);
        double sinB = sin(angleB * M_PI / 180.0);
        double sinC = sin(angleC * M_PI / 180.0);
        
        if (fabs(sideA / sinA - sideB / sinB) > eps ||
            fabs(sideA / sinA - sideC / sinC) > eps)
            return false;
        
        return true;
    }

    // Вычисление углов по сторонам (теорема косинусов)
    void calculateAnglesFromSides() {
        angleA = acos((sideB*sideB + sideC*sideC - sideA*sideA) / (2*sideB*sideC)) * 180.0 / M_PI;
        angleB = acos((sideA*sideA + sideC*sideC - sideB*sideB) / (2*sideA*sideC)) * 180.0 / M_PI;
        angleC = 180.0 - angleA - angleB;
    }

    // Вычисление сторон по углам и одной стороне (теорема синусов)
    void calculateSidesFromAngles() {
        double sinA = sin(angleA * M_PI / 180.0);
        double sinB = sin(angleB * M_PI / 180.0);
        double sinC = sin(angleC * M_PI / 180.0);
        
        sideB = sideA * sinB / sinA;
        sideC = sideA * sinC / sinA;
    }

public:
    // Конструктор по умолчанию
    Triangle() : sideA(3), sideB(4), sideC(5), 
                 angleA(0), angleB(0), angleC(0) {
        calculateAnglesFromSides();
    }

    // Конструктор инициализации (по трем сторонам)
    Triangle(double a, double b, double c) : sideA(a), sideB(b), sideC(c) {
        calculateAnglesFromSides();
        if (!exists()) {
            cout << "Ошибка: треугольник с такими сторонами не существует!" << endl;
            // Устанавливаем треугольник по умолчанию
            sideA = 3; sideB = 4; sideC = 5;
            calculateAnglesFromSides();
        }
    }

    // Конструктор инициализации (по стороне и двум углам)
    Triangle(double side, double angA, double angB, bool bySideAndAngles) {
        if (bySideAndAngles) {
            sideA = side;
            angleA = angA;
            angleB = angB;
            angleC = 180.0 - angleA - angleB;
            calculateSidesFromAngles();
            
            if (!exists()) {
                cout << "Ошибка: треугольник с такими параметрами не существует!" << endl;
                sideA = 3; sideB = 4; sideC = 5;
                calculateAnglesFromSides();
            }
        }
    }

    // Конструктор копирования
    Triangle(const Triangle& other) {
        sideA = other.sideA;
        sideB = other.sideB;
        sideC = other.sideC;
        angleA = other.angleA;
        angleB = other.angleB;
        angleC = other.angleC;
    }

    // Деструктор
    ~Triangle() {}

    // Геттеры для полей
    double getSideA() const { return sideA; }
    double getSideB() const { return sideB; }
    double getSideC() const { return sideC; }
    double getAngleA() const { return angleA; }
    double getAngleB() const { return angleB; }
    double getAngleC() const { return angleC; }

    // Сеттеры для полей
    void setSideA(double a) {
        double oldA = sideA, oldB = sideB, oldC = sideC;
        sideA = a;
        calculateAnglesFromSides();
        if (!exists()) {
            cout << "Ошибка: изменение стороны приведет к несуществующему треугольнику!" << endl;
            sideA = oldA; sideB = oldB; sideC = oldC;
            calculateAnglesFromSides();
        }
    }

    void setSideB(double b) {
        double oldA = sideA, oldB = sideB, oldC = sideC;
        sideB = b;
        calculateAnglesFromSides();
        if (!exists()) {
            cout << "Ошибка: изменение стороны приведет к несуществующему треугольнику!" << endl;
            sideA = oldA; sideB = oldB; sideC = oldC;
            calculateAnglesFromSides();
        }
    }

    void setSideC(double c) {
        double oldA = sideA, oldB = sideB, oldC = sideC;
        sideC = c;
        calculateAnglesFromSides();
        if (!exists()) {
            cout << "Ошибка: изменение стороны приведет к несуществующему треугольнику!" << endl;
            sideA = oldA; sideB = oldB; sideC = oldC;
            calculateAnglesFromSides();
        }
    }

    // Вычисление площади (формула Герона)
    double area() const {
        double p = perimeter() / 2;
        return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
    }

    // Вычисление периметра
    double perimeter() const {
        return sideA + sideB + sideC;
    }

    // Вычисление высот
    double heightToSideA() const {
        return 2 * area() / sideA;
    }

    double heightToSideB() const {
        return 2 * area() / sideB;
    }

    double heightToSideC() const {
        return 2 * area() / sideC;
    }

    // Определение вида треугольника
    string getType() const {
        const double eps = 1e-6;
        
        // Проверка на равносторонний
        if (fabs(sideA - sideB) < eps && fabs(sideB - sideC) < eps)
            return "равносторонний";
        
        // Проверка на равнобедренный
        if (fabs(sideA - sideB) < eps || fabs(sideA - sideC) < eps || fabs(sideB - sideC) < eps)
            return "равнобедренный";
        
        // Проверка на прямоугольный (теорема Пифагора)
        double sides[3] = {sideA, sideB, sideC};
        sort(sides, sides + 3);
        if (fabs(sides[2]*sides[2] - (sides[0]*sides[0] + sides[1]*sides[1])) < eps)
            return "прямоугольный";
        
        return "разносторонний";
    }

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const Triangle& t) {
        os << "Треугольник:" << endl;
        os << "  Стороны: a = " << t.sideA << ", b = " << t.sideB << ", c = " << t.sideC << endl;
        os << "  Углы: A = " << t.angleA << "°, B = " << t.angleB << "°, C = " << t.angleC << "°" << endl;
        os << "  Периметр: " << t.perimeter() << endl;
        os << "  Площадь: " << t.area() << endl;
        os << "  Тип: " << t.getType() << endl;
        return os;
    }

    // Перегрузка оператора ввода
    friend istream& operator>>(istream& is, Triangle& t) {
        cout << "Введите стороны треугольника (a b c): ";
        double a, b, c;
        is >> a >> b >> c;
        Triangle temp(a, b, c);
        t = temp;
        return is;
    }

    // Перегрузка оператора сложения (объединение площадей? - для демонстрации)
    double operator+(const Triangle& other) const {
        return this->area() + other.area();
    }

    // Перегрузка оператора вычитания (разность площадей)
    double operator-(const Triangle& other) const {
        return fabs(this->area() - other.area());
    }

    // Перегрузка оператора умножения на число (масштабирование треугольника)
    Triangle operator*(double scalar) const {
        return Triangle(sideA * scalar, sideB * scalar, sideC * scalar);
    }

    // Перегрузка оператора деления на число
    Triangle operator/(double scalar) const {
        if (scalar == 0) {
            cout << "Ошибка: деление на ноль!" << endl;
            return *this;
        }
        return Triangle(sideA / scalar, sideB / scalar, sideC / scalar);
    }

    // Перегрузка операторов сравнения (сравниваем по площади)
    bool operator==(const Triangle& other) const {
        const double eps = 1e-6;
        return fabs(this->area() - other.area()) < eps;
    }

    bool operator!=(const Triangle& other) const {
        return !(*this == other);
    }

    bool operator>(const Triangle& other) const {
        return this->area() > other.area();
    }

    bool operator<(const Triangle& other) const {
        return this->area() < other.area();
    }

    bool operator>=(const Triangle& other) const {
        return this->area() >= other.area();
    }

    bool operator<=(const Triangle& other) const {
        return this->area() <= other.area();
    }

    // Перегрузка оператора присваивания
    Triangle& operator=(const Triangle& other) {
        if (this != &other) {
            sideA = other.sideA;
            sideB = other.sideB;
            sideC = other.sideC;
            angleA = other.angleA;
            angleB = other.angleB;
            angleC = other.angleC;
        }
        return *this;
    }

    // Перегрузка оператора индексации для доступа к сторонам
    double& operator[](int index) {
        if (index == 0) return sideA;
        if (index == 1) return sideB;
        if (index == 2) return sideC;
        throw out_of_range("Индекс должен быть от 0 до 2");
    }

    const double& operator[](int index) const {
        if (index == 0) return sideA;
        if (index == 1) return sideB;
        if (index == 2) return sideC;
        throw out_of_range("Индекс должен быть от 0 до 2");
    }
};

// Перегрузка оператора умножения числа на треугольник (для коммутативности)
Triangle operator*(double scalar, const Triangle& t) {
    return t * scalar;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "=== Демонстрация работы с классом Triangle ===" << endl;
    
    // Различные способы создания объектов
    cout << "\n1. Создание объектов разными конструкторами:" << endl;
    
    // Конструктор по умолчанию
    Triangle t1;
    cout << "t1 (конструктор по умолчанию):" << endl << t1 << endl;
    
    // Конструктор инициализации (по трем сторонам)
    Triangle t2(5, 6, 7);
    cout << "t2 (стороны 5, 6, 7):" << endl << t2 << endl;
    
    // Конструктор инициализации (по стороне и двум углам)
    Triangle t3(10, 45, 60, true);
    cout << "t3 (сторона 10, углы 45° и 60°):" << endl << t3 << endl;
    
    // Конструктор копирования
    Triangle t4(t2);
    cout << "t4 (копия t2):" << endl << t4 << endl;
    
    // Создание массива объектов
    cout << "\n2. Создание массива объектов:" << endl;
    Triangle triangles[3] = {
        Triangle(3, 4, 5),      // прямоугольный
        Triangle(5, 5, 5),      // равносторонний
        Triangle(7, 7, 10)      // равнобедренный
    };
    
    for (int i = 0; i < 3; i++) {
        cout << "triangles[" << i << "]:" << endl << triangles[i] << endl;
    }
    
    // Демонстрация методов
    cout << "\n3. Демонстрация методов:" << endl;
    cout << "t2 периметр: " << t2.perimeter() << endl;
    cout << "t2 площадь: " << t2.area() << endl;
    cout << "t2 высоты: к стороне a = " << t2.heightToSideA() 
         << ", к b = " << t2.heightToSideB() 
         << ", к c = " << t2.heightToSideC() << endl;
    cout << "t2 тип: " << t2.getType() << endl;
    
    // Демонстрация перегруженных операций
    cout << "\n4. Демонстрация перегруженных операций:" << endl;
    
    // Операции с треугольниками
    cout << "t1 + t2 (сумма площадей): " << (t1 + t2) << endl;
    cout << "t1 - t2 (разность площадей): " << (t1 - t2) << endl;
    
    // Умножение на скаляр
    Triangle t5 = t2 * 2;
    cout << "t5 = t2 * 2:" << endl << t5 << endl;
    
    // Деление на скаляр
    Triangle t6 = t2 / 2;
    cout << "t6 = t2 / 2:" << endl << t6 << endl;
    
    // Коммутативность умножения
    Triangle t7 = 1.5 * t2;
    cout << "t7 = 1.5 * t2:" << endl << t7 << endl;
    
    // Операторы сравнения
    cout << "Сравнение треугольников по площади:" << endl;
    cout << "t1 == t2: " << (t1 == t2 ? "true" : "false") << endl;
    cout << "t1 != t2: " << (t1 != t2 ? "true" : "false") << endl;
    cout << "t1 > t2: " << (t1 > t2 ? "true" : "false") << endl;
    cout << "t1 < t2: " << (t1 < t2 ? "true" : "false") << endl;
    
    // Оператор индексации
    cout << "\n5. Оператор индексации:" << endl;
    cout << "t2[0] (сторона a): " << t2[0] << endl;
    cout << "t2[1] (сторона b): " << t2[1] << endl;
    cout << "t2[2] (сторона c): " << t2[2] << endl;
    
    // Изменение через оператор индексации
    t2[0] = 8;
    cout << "После t2[0] = 8:" << endl << t2 << endl;
    
    // Использование геттеров и сеттеров
    cout << "\n6. Демонстрация геттеров и сеттеров:" << endl;
    cout << "Текущая сторона a треугольника t2: " << t2.getSideA() << endl;
    t2.setSideB(9);
    cout << "После установки стороны b = 9:" << endl << t2 << endl;
    
    // Попытка создания несуществующего треугольника
    cout << "\n7. Попытка создания несуществующего треугольника:" << endl;
    Triangle t8(1, 2, 10);
    
    // Ввод с клавиатуры
    cout << "\n8. Ввод треугольника с клавиатуры:" << endl;
    Triangle t9;
    cin >> t9;
    cout << "Введенный треугольник:" << endl << t9 << endl;
    
    return 0;
}
