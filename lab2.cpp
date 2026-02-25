#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// 1. РЕАЛИЗАЦИЯ ЧЕРЕЗ СТРУКТУРУ И ВНЕШНИЕ ФУНКЦИИ

struct TriangleStruct {
    double a, b, c;   // стороны
    double A, B, C;   // углы (в градусах)
};

// Вспомогательная функция для проверки существования треугольника
bool isTriangle(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

// Перевод радиан в градусы
double toDegrees(double rad) {
    return rad * 180.0 / M_PI;
}

// Инициализация (контроль корректности)
void init(TriangleStruct& t, double a, double b, double c) {
    if (!isTriangle(a, b, c)) {
        cout << "Ошибка: треугольник с такими сторонами не существует!\n";
        return;
    }
    t.a = a; t.b = b; t.c = c;

    // Вычисляем углы по теореме косинусов
    t.A = toDegrees(acos((b*b + c*c - a*a) / (2*b*c)));
    t.B = toDegrees(acos((a*a + c*c - b*b) / (2*a*c)));
    t.C = 180.0 - t.A - t.B;
}

// Ввод с клавиатуры
void read(TriangleStruct& t) {
    double a, b, c;
    cout << "Введите стороны треугольника (a b c): ";
    cin >> a >> b >> c;
    init(t, a, b, c);
}

// Вывод на экран
void display(const TriangleStruct& t) {
    cout << "Стороны: a=" << t.a << ", b=" << t.b << ", c=" << t.c << endl;
    cout << "Углы:   A=" << t.A << "°, B=" << t.B << "°, C=" << t.C << "°" << endl;
}

// Преобразование в строку
string toString(const TriangleStruct& t) {
    ostringstream oss;
    oss << "Triangle(a=" << t.a << ", b=" << t.b << ", c=" << t.c
        << ", A=" << t.A << "°, B=" << t.B << "°, C=" << t.C << "°)";
    return oss.str();
}

// Получение площади (формула Герона)
double area(const TriangleStruct& t) {
    double p = (t.a + t.b + t.c) / 2.0;
    return sqrt(p * (p - t.a) * (p - t.b) * (p - t.c));
}

// Получение периметра
double perimeter(const TriangleStruct& t) {
    return t.a + t.b + t.c;
}

// Получение высот (ha = 2*S / a)
void heights(const TriangleStruct& t, double& ha, double& hb, double& hc) {
    double s = area(t);
    ha = 2 * s / t.a;
    hb = 2 * s / t.b;
    hc = 2 * s / t.c;
}

// Определение вида треугольника
string triangleType(const TriangleStruct& t) {
    const double eps = 1e-7;
    bool eqAB = fabs(t.a - t.b) < eps;
    bool eqBC = fabs(t.b - t.c) < eps;
    bool eqAC = fabs(t.a - t.c) < eps;

    if (eqAB && eqBC) return "равносторонний";
    if (eqAB || eqBC || eqAC) return "равнобедренный";

    // Проверка на прямоугольность (теорема Пифагора)
    double sides[3] = {t.a, t.b, t.c};
    sort(sides, sides + 3);
    if (fabs(sides[2]*sides[2] - (sides[0]*sides[0] + sides[1]*sides[1])) < eps)
        return "прямоугольный";

    return "разносторонний";
}

// 2. РЕАЛИЗАЦИЯ ЧЕРЕЗ КЛАСС С ЗАКРЫТЫМИ ПОЛЯМИ

class TriangleClass {
private:
    double a, b, c;   // стороны
    double A, B, C;   // углы (в градусах)

    // Внутренний метод для вычисления углов по сторонам
    void computeAngles() {
        A = toDegrees(acos((b*b + c*c - a*a) / (2*b*c)));
        B = toDegrees(acos((a*a + c*c - b*b) / (2*a*c)));
        C = 180.0 - A - B;
    }

    bool checkTriangle(double a_, double b_, double c_) const {
        return (a_ + b_ > c_) && (a_ + c_ > b_) && (b_ + c_ > a_);
    }

public:
    // Конструктор / инициализация
    void init(double a_, double b_, double c_) {
        if (!checkTriangle(a_, b_, c_)) {
            cout << "Ошибка: треугольник не существует!\n";
            return;
        }
        a = a_; b = b_; c = c_;
        computeAngles();
    }

    // Ввод с клавиатуры
    void read() {
        double a_, b_, c_;
        cout << "Введите стороны треугольника (a b c): ";
        cin >> a_ >> b_ >> c_;
        init(a_, b_, c_);
    }

    // Вывод на экран
    void display() const {
        cout << "Стороны: a=" << a << ", b=" << b << ", c=" << c << endl;
        cout << "Углы:   A=" << A << "°, B=" << B << "°, C=" << C << "°" << endl;
    }

    // Преобразование в строку
    string toString() const {
        ostringstream oss;
        oss << "Triangle(a=" << a << ", b=" << b << ", c=" << c
            << ", A=" << A << "°, B=" << B << "°, C=" << C << "°)";
        return oss.str();
    }

    // Доступ к полям (геттеры)
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    double getAngleA() const { return A; }
    double getAngleB() const { return B; }
    double getAngleC() const { return C; }

    // Изменение сторон (сеттеры с пересчётом)
    void setSides(double a_, double b_, double c_) {
        if (!checkTriangle(a_, b_, c_)) {
            cout << "Ошибка: новые стороны не образуют треугольник!\n";
            return;
        }
        a = a_; b = b_; c = c_;
        computeAngles();
    }

    // Площадь
    double area() const {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    // Периметр
    double perimeter() const {
        return a + b + c;
    }

    // Высоты
    void heights(double& ha, double& hb, double& hc) const {
        double s = area();
        ha = 2 * s / a;
        hb = 2 * s / b;
        hc = 2 * s / c;
    }

    // Тип треугольника
    string type() const {
        const double eps = 1e-7;
        bool eqAB = fabs(a - b) < eps;
        bool eqBC = fabs(b - c) < eps;
        bool eqAC = fabs(a - c) < eps;

        if (eqAB && eqBC) return "равносторонний";
        if (eqAB || eqBC || eqAC) return "равнобедренный";

        double sides[3] = {a, b, c};
        sort(sides, sides + 3);
        if (fabs(sides[2]*sides[2] - (sides[0]*sides[0] + sides[1]*sides[1])) < eps)
            return "прямоугольный";

        return "разносторонний";
    }
};

//------------------------------------------------------------------------------
// ГЛАВНАЯ ФУНКЦИЯ (ДЕМОНСТРАЦИЯ)
//------------------------------------------------------------------------------

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "===== Демонстрация структуры TriangleStruct =====\n";
    TriangleStruct ts;
    read(ts);
    display(ts);
    cout << "toString: " << toString(ts) << endl;
    cout << "Площадь: " << area(ts) << endl;
    cout << "Периметр: " << perimeter(ts) << endl;
    double ha, hb, hc;
    heights(ts, ha, hb, hc);
    cout << "Высоты: ha=" << ha << ", hb=" << hb << ", hc=" << hc << endl;
    cout << "Тип треугольника: " << triangleType(ts) << endl;

    cout << "\n===== Демонстрация класса TriangleClass =====\n";
    TriangleClass tc;
    tc.read();
    tc.display();
    cout << "toString: " << tc.toString() << endl;
    cout << "Площадь: " << tc.area() << endl;
    cout << "Периметр: " << tc.perimeter() << endl;
    tc.heights(ha, hb, hc);
    cout << "Высоты: ha=" << ha << ", hb=" << hb << ", hc=" << hc << endl;
    cout << "Тип треугольника: " << tc.type() << endl;

    // Демонстрация изменения сторон
    cout << "\nИзменяем стороны на 5, 5, 8:\n";
    tc.setSides(5, 5, 8);
    tc.display();
    cout << "Тип треугольника: " << tc.type() << endl;

    return 0;
}
