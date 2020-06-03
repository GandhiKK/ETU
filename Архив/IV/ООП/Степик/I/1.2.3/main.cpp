#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define Cntr_X center.get_x()
#define Cntr_Y center.get_y()
#define ShapeRed shape.get_color().get_red()
#define ShapeGreen shape.get_color().get_green()
#define ShapeBlue shape.get_color().get_blue()

class Point
{
public:
    Point(double x = 0, double y = 0)
        : x(x)
        , y(y)
    {
    };

    double get_x() const { return x; }
    double get_y() const { return y; }
    void set_x(double x) { this->x = x; }
    void set_y(double y) { this->y = y; }
private:
    double x, y;
};

class Color
{
public:
    Color(unsigned int red, unsigned int green, unsigned int blue)
        : red(red)
        , green(green)
        , blue(blue)
    {
    };

    unsigned int get_red() const { return red; }
    unsigned int get_green() const { return green; }
    unsigned int get_blue() const { return blue; }
private:
    unsigned int red, green, blue;
};

class Shape
{
public:
    Shape(Color color, Point center)
        : color(color)
        , center(center)
    {
    }

    void set_color(Color color) { this->color = color; } //Установка цвета
    Color get_color() const { return color; } //Получение цвета

    virtual void scaling(double scale) = 0; //Масштабирование объекта на заданный коэффициент
    virtual ostream& printObject(ostream& stream, Shape& shape) = 0; //Вывод в поток
    friend ostream& operator << (ostream& stream, Shape& shape) //Оператор вывода в поток
    {
        return shape.printObject(stream, shape);
    }

    void moving(Point point) //Перемещение объекта в указанные координаты
    {
        size_t index = 0;
        double X_off = point.get_x() - Cntr_X;
        double Y_off = point.get_y() - Cntr_Y;
        center = point;
        while (index != points.size())
        {
            double temp_x = points[index].get_x() + X_off;
            double temp_y = points[index].get_y() + Y_off;
            points[index].set_x(temp_x);
            points[index].set_y(temp_y);
            ++index;
        }
    }

    void rotation(double grade) //Поворот объекта на заданный угол
    {
        double ex_grade = grade*M_PI/180.0;
        size_t index = 0;
        while (index != points.size())
        {
            //Матрица поворота
            //Координаты (x′,y′) в результате поворота точки (x, y) имеют вид:
            //x' = x cos() - y sin()
            //y' = x sin() + y cos()
            int current_x = points[index].get_x() - Cntr_X;
            int current_y = points[index].get_y() - Cntr_Y;
            double ex_x = Cntr_X + current_x * cos(ex_grade) - current_y * sin(ex_grade);
            double ex_y = Cntr_Y + current_x * sin(ex_grade) + current_y * cos(ex_grade);
            points[index].set_x(ex_x);
            points[index].set_y(ex_y);
            ++index;
        }
    }
protected:
    Color color;
    Point center;
    vector <Point> points;
};

class Square : public Shape //Класс объекта квадрат
{
public:
    Square(double lenght, Color color, Point center)
        : Shape(color, center)
    {
        this->lenght = lenght;
        int set_x1 = Cntr_X - lenght / 2;
        int set_y1 = Cntr_Y - lenght / 2;
        int set_x2 = Cntr_X + lenght / 2;
        int set_y2 = Cntr_Y + lenght / 2;
        points.push_back(Point(set_x1, set_y1));
        points.push_back(Point(set_x2, set_y1));
        points.push_back(Point(set_x2, set_y2));
        points.push_back(Point(set_x1, set_y2));
    }

    void scaling(double scale) override //Масштабирование
    {
        double x;
        double y;
        size_t index = 0;
        lenght *= scale;
        while (index != points.size())
        {
            x = Cntr_X + (points[index].get_x() - Cntr_X)*scale;
            y = Cntr_Y + (points[index].get_y() - Cntr_Y)*scale;
            points[index].set_x(x);
            points[index].set_y(y);
            ++index;
        }
    }

    ostream& printObject(ostream& stream, Shape& shape) override //Вывод в поток
    {
        size_t index = 0;
        stream << "SQUARE\n";
        stream << "Color: (" << ShapeRed << ", " << ShapeGreen << ", " << ShapeBlue << ")\n";
        stream << "Coordinates: \n";
        while (index != points.size())
        {
            stream << "  (" << points[index].get_x() << "; " << points[index].get_y() << ")\n";
            ++index;
        }
        stream << "------------------------\n";
        return stream;
    }
private:
    double lenght;
};

class Parallelogram : public Shape { //Класс объекта параллелограм
public:
    Parallelogram(Color color, Point point1, Point point2, Point point3)
        : Shape(color, center)
    {
        this->point1 = point1;
        this->point2 = point2;
        this->point3 = point3;
        points.push_back(point1);
        points.push_back(point2);
        points.push_back(point3);
        int x1 = points[0].get_x();
        int x2 = points[1].get_x();
        int x3 = points[2].get_x();
        int y1 = points[0].get_y();
        int y2 = points[1].get_y();
        int y3 = points[2].get_y();
        points.push_back(Point(x1 + x3 - x2, y3 - y2 + y1));
        center.set_x((x1+ x3) / 2);
        center.set_y((y1 + y3) / 2);
    }

    void scaling(double scale) override //Масштабирование
    {
        double x;
        double y;
        size_t index = 0;
        while (index != points.size())
        {
            x = Cntr_X + (points[index].get_x() - Cntr_X)*scale;
            y = Cntr_Y + (points[index].get_y() - Cntr_Y)*scale;
            points[index].set_x(x);
            points[index].set_y(y);
            ++index;
        }
    }

    ostream& printObject(ostream& stream, Shape& shape) override //Вывод в поток
    {
        size_t index = 0;
        stream << "PARALLELOGRAM\n";
        stream << "Color: (" << ShapeRed << ", " << ShapeGreen << ", " << ShapeBlue << ")\n";
        stream << "Center: (" << Cntr_X << "; " << Cntr_Y << ")\n";
        stream << "Coordinates: \n";
        while (index != points.size())
        {
            stream << "  (" << points[index].get_x() << "; " << points[index].get_y() << ")\n";
            ++index;
        }
        stream << "------------------------\n";
        return stream;
    }
private:
    Point point1, point2, point3;
};

class Rhombus : public Shape //Класс объекта ромб
{
public:
    Rhombus(double diag1, double diag2, Point point, Color color)
        : Shape(color, center)
    {
        this->diag1 = diag1;
        this->diag2 = diag2;
        points.push_back(point);
        points.push_back(Point(point.get_x() - diag2 / 2, diag1 / 2));
        points.push_back(Point(point.get_x(), point.get_y() + diag1));
        points.push_back(Point(point.get_x() + diag2 / 2, diag1 / 2));
        center.set_x((points[1].get_x() + points[3].get_x()) / 2);
        center.set_y((points[0].get_y() + points[2].get_y()) / 2);
    }

    void scaling(double scale) override //Масштабирование
    {
        double x;
        double y;
        size_t index = 0;
        diag1 *= scale;
        diag2 *= scale;
        while (index != points.size())
        {
            x = Cntr_X + (points[index].get_x() - Cntr_X)*scale;
            y = Cntr_Y + (points[index].get_y() - Cntr_Y)*scale;
            points[index].set_x(x);
            points[index].set_y(y);
            ++index;
        }
    }

    ostream& printObject(ostream& stream, Shape& shape) override //Вывод в поток
    {
        size_t index = 0;
        stream << "RHOMBUS\n";
        stream << "Color: (" << ShapeRed << ", " << ShapeGreen << ", " << ShapeBlue << ")\n";
        stream << "Center: (" << Cntr_X << "; " << Cntr_Y << ")\n";
        stream << "Coordinates: " << endl;
        while (index != points.size())
        {
            stream << "  (" << points[index].get_x() << "; " << points[index].get_y() << ")\n";
            ++index;
        }
        stream << "------------------------\n";
        return stream;
    }
private:
    double diag1, diag2;
};

int main()
{
    Square first_example(3, {100, 120, 140}, {5, 3}); //Длина стороны, цвет, центр
    cout << first_example;
    cout << "Object scaling:\n";
    first_example.scaling(3); //Масштабирование объекта
    cout << first_example;

    Parallelogram second_example({150, 150, 150}, {1, 2}, {2, 5}, {7, 2}); //Цвет, три точки
    cout << second_example;
    cout << "Object rotation:\n";
    second_example.rotation(40); //Поворот объекта
    cout << second_example;

    Rhombus third_example(5, 2, {2, 2}, {56, 67, 78}); //Диагональ, диагональ, точка, цвет
    cout << third_example;
    cout << "Object moving:\n";
    third_example.moving({3, 6}); //Перемещение объекта
    cout << third_example;
    return 0;
}
