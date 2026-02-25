#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Triangle {
private:
    // Стороны треугольника
    double sideA;
    double sideB;
    double sideC;
    
    // Углы треугольника (в градусах)
    double angleA; // угол напротив стороны A
    double angleB; // угол напротив стороны B
    double angleC; // угол напротив стороны C
    
    // Приватный метод для проверки существования треугольника
    bool isValidTriangle(double a, double b, double c) {
        // Проверка неравенства треугольника
        return (a + b > c) && (a + c > b) && (b + c > a);
    }
    
    // Приватный метод для вычисления углов по сторонам (теорема косинусов)
    void calculateAngles() {
        angleA = acos((sideB * sideB + sideC * sideC - sideA * sideA) / (2 * sideB * sideC)) * 180.0 / M_PI;
        angleB = acos((sideA * sideA + sideC * sideC - sideB * sideB) / (2 * sideA * sideC)) * 180.0 / M_PI;
        angleC = 180.0 - angleA - angleB;
    }
    
    // Приватный метод для вычисления сторон по углу и двум сторонам
    void calculateSideFromAngles() {
        // Используем теорему синусов для коррекции сторон, если заданы углы
        // В данной реализации мы полагаемся на заданные стороны
    }
    
public:
    // Конструктор без аргументов (по умолчанию)
    // Создает равносторонний треугольник со стороной 1
    Triangle() : sideA(1.0), sideB(1.0), sideC(1.0) {
        calculateAngles();
        cout << "Вызван конструктор по умолчанию" << endl;
    }
    
    // Конструктор инициализации (по трем сторонам)
    Triangle(double a, double b, double c) {
        if (isValidTriangle(a, b, c)) {
            sideA = a;
            sideB = b;
            sideC = c;
            calculateAngles();
            cout << "Вызван конструктор инициализации (по сторонам)" << endl;
        } else {
            cout << "Ошибка: треугольник с такими сторонами не существует. Создан треугольник по умолчанию." << endl;
            sideA = sideB = sideC = 1.0;
            calculateAngles();
        }
    }
    
    // Конструктор инициализации (по стороне и двум углам)
    Triangle(double a, double angleB, double angleC, bool byAngles) {
        // byAngles - флаг для отличия от конструктора по трем сторонам
        double b, c;
        double angleA = 180.0 - angleB - angleC;
        
        // По теореме синусов: a/sin(A) = b/sin(B) = c/sin(C)
        double sinA = sin(angleA * M_PI / 180.0);
        double sinB = sin(angleB * M_PI / 180.0);
        double sinC = sin(angleC * M_PI / 180.0);
        
        b = a * sinB / sinA;
        c = a * sinC / sinA;
        
        if (isValidTriangle(a, b, c)) {
            sideA = a;
            sideB = b;
            sideC = c;
            this->angleA = angleA;
            this->angleB = angleB;
            this->angleC = angleC;
            cout << "Вызван конструктор инициализации (по стороне и двум углам)" << endl;
        } else {
            cout << "Ошибка: треугольник с такими параметрами не существует. Создан треугольник по умолчанию." << endl;
            sideA = sideB = sideC = 1.0;
            calculateAngles();
        }
    }
    
    // Конструктор копирования
    Triangle(const Triangle &other) {
        sideA = other.sideA;
        sideB = other.sideB;
        sideC = other.sideC;
        angleA = other.angleA;
        angleB = other.angleB;
        angleC = other.angleC;
        cout << "Вызван конструктор копирования" << endl;
    }
    
    // Деструктор
    ~Triangle() {
        cout << "Вызван деструктор для треугольника со сторонами: " 
             << sideA << ", " << sideB << ", " << sideC << endl;
    }
    
    // Методы получения полей данных
    double getSideA() const { return sideA; }
    double getSideB() const { return sideB; }
    double getSideC() const { return sideC; }
    double getAngleA() const { return angleA; }
    double getAngleB() const { return angleB; }
    double getAngleC() const { return angleC; }
    
    // Методы изменения полей данных
    void setSides(double a, double b, double c) {
        if (isValidTriangle(a, b, c)) {
            sideA = a;
            sideB = b;
            sideC = c;
            calculateAngles();
        } else {
            cout << "Ошибка: треугольник с такими сторонами не существует. Значения не изменены." << endl;
        }
    }
    
    void setSideA(double a) {
        if (isValidTriangle(a, sideB, sideC)) {
            sideA = a;
            calculateAngles();
        } else {
            cout << "Ошибка: изменение стороны приведет к несуществующему треугольнику." << endl;
        }
    }
    
    void setSideB(double b) {
        if (isValidTriangle(sideA, b, sideC)) {
            sideB = b;
            calculateAngles();
        } else {
            cout << "Ошибка: изменение стороны приведет к несуществующему треугольнику." << endl;
        }
    }
    
    void setSideC(double c) {
        if (isValidTriangle(sideA, sideB, c)) {
            sideC = c;
            calculateAngles();
        } else {
            cout << "Ошибка: изменение стороны приведет к несуществующему треугольнику." << endl;
        }
    }
    
    // Вычисление площади (по формуле Герона)
    double calculateArea() const {
        double p = calculatePerimeter() / 2.0;
        return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
    }
    
    // Вычисление периметра
    double calculatePerimeter() const {
        return sideA + sideB + sideC;
    }
    
    // Вычисление высот
    double calculateHeightToSideA() const {
        return 2.0 * calculateArea() / sideA;
    }
    
    double calculateHeightToSideB() const {
        return 2.0 * calculateArea() / sideB;
    }
    
    double calculateHeightToSideC() const {
        return 2.0 * calculateArea() / sideC;
    }
    
    // Определение вида треугольника
    string getTriangleType() const {
        const double EPSILON = 1e-10;
        
        // Проверка на равносторонний
        if (fabs(sideA - sideB) < EPSILON && fabs(sideB - sideC) < EPSILON) {
            return "равносторонний";
        }
        
        // Проверка на равнобедренный
        if (fabs(sideA - sideB) < EPSILON || fabs(sideB - sideC) < EPSILON || fabs(sideA - sideC) < EPSILON) {
            // Проверка на прямоугольный равнобедренный
            if (isRightAngled()) {
                return "прямоугольный равнобедренный";
            }
            return "равнобедренный";
        }
        
        // Проверка на прямоугольный
        if (isRightAngled()) {
            return "прямоугольный";
        }
        
        return "разносторонний";
    }
    
    // Проверка на прямоугольный треугольник
    bool isRightAngled() const {
        const double EPSILON = 1e-10;
        double a2 = sideA * sideA;
        double b2 = sideB * sideB;
        double c2 = sideC * sideC;
        
        return (fabs(a2 + b2 - c2) < EPSILON) ||
               (fabs(a2 + c2 - b2) < EPSILON) ||
               (fabs(b2 + c2 - a2) < EPSILON);
    }
    
    // Метод для вывода информации о треугольнике
    void display() const {
        cout << "\n=== Информация о треугольнике ===" << endl;
        cout << "Стороны: a = " << sideA << ", b = " << sideB << ", c = " << sideC << endl;
        cout << "Углы (в градусах): A = " << angleA << ", B = " << angleB << ", C = " << angleC << endl;
        cout << "Периметр: " << calculatePerimeter() << endl;
        cout << "Площадь: " << calculateArea() << endl;
        cout << "Высоты: h_a = " << calculateHeightToSideA() 
             << ", h_b = " << calculateHeightToSideB() 
             << ", h_c = " << calculateHeightToSideC() << endl;
        cout << "Тип треугольника: " << getTriangleType() << endl;
        cout << "===================================\n" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "=== Демонстрация работы с классом Triangle ===" << endl;
    
    // 1. Создание объектов разными конструкторами
    cout << "\n--- 1. Создание объектов ---" << endl;
    
    // Конструктор по умолчанию
    cout << "\nСоздание объекта t1 (конструктор по умолчанию):" << endl;
    Triangle t1;
    t1.display();
    
    // Конструктор инициализации (по трем сторонам)
    cout << "\nСоздание объекта t2 (конструктор инициализации, стороны 3, 4, 5):" << endl;
    Triangle t2(3.0, 4.0, 5.0);
    t2.display();
    
    // Конструктор инициализации (по стороне и двум углам)
    cout << "\nСоздание объекта t3 (конструктор инициализации, сторона 5, углы 30 и 60):" << endl;
    Triangle t3(5.0, 30.0, 60.0, true);
    t3.display();
    
    // Конструктор копирования
    cout << "\nСоздание объекта t4 (конструктор копирования из t2):" << endl;
    Triangle t4(t2);
    t4.display();
    
    // 2. Демонстрация массивов объектов
    cout << "\n--- 2. Массивы объектов ---" << endl;
    
    // Статический массив объектов (вызов конструктора по умолчанию для каждого элемента)
    cout << "\nСоздание статического массива из 3 объектов (конструктор по умолчанию):" << endl;
    Triangle tArray1[3];
    
    // Статический массив с инициализацией
    cout << "\nСоздание статического массива с инициализацией:" << endl;
    Triangle tArray2[3] = { Triangle(2.0, 2.0, 3.0), Triangle(5.0, 5.0, 5.0), Triangle(3.0, 4.0, 5.0) };
    
    // Динамический массив объектов
    cout << "\nСоздание динамического массива из 2 объектов:" << endl;
    Triangle* tArray3 = new Triangle[2];
    
    cout << "\nОсвобождение динамического массива:" << endl;
    delete[] tArray3;
    
    // 3. Демонстрация методов
    cout << "\n--- 3. Демонстрация методов ---" << endl;
    
    Triangle t5(6.0, 6.0, 8.0);
    t5.display();
    
    cout << "Изменение стороны A на 7.0:" << endl;
    t5.setSideA(7.0);
    t5.display();
    
    cout << "Попытка изменить стороны на (1, 2, 10) - некорректный треугольник:" << endl;
    t5.setSides(1.0, 2.0, 10.0);
    
    cout << "\nПолучение значений полей через геттеры:" << endl;
    cout << "Сторона A: " << t2.getSideA() << endl;
    cout << "Угол B: " << t2.getAngleB() << " градусов" << endl;
    
    // 4. Демонстрация всех операций с разными треугольниками
    cout << "\n--- 4. Демонстрация всех операций с разными треугольниками ---" << endl;
    
    // Равносторонний треугольник
    Triangle t6(5.0, 5.0, 5.0);
    cout << "\nРавносторонний треугольник:" << endl;
    t6.display();
    
    // Равнобедренный треугольник
    Triangle t7(5.0, 5.0, 8.0);
    cout << "\nРавнобедренный треугольник:" << endl;
    t7.display();
    
    // Прямоугольный треугольник
    Triangle t8(3.0, 4.0, 5.0);
    cout << "\nПрямоугольный треугольник:" << endl;
    t8.display();
    
    // Проверка типа для разных треугольников
    cout << "\n--- 5. Проверка типа треугольников ---" << endl;
    cout << "t6 (5,5,5) - " << t6.getTriangleType() << endl;
    cout << "t7 (5,5,8) - " << t7.getTriangleType() << endl;
    cout << "t8 (3,4,5) - " << t8.getTriangleType() << endl;
    
    // Демонстрация вызова деструкторов
    cout << "\n--- Завершение работы программы (деструкторы будут вызваны автоматически) ---" << endl;
    
    return 0;
}
