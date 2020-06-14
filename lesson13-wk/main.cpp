#include <iostream>
#include <iomanip>
using namespace std;
class Shape
{
public:
    Shape() {}
    virtual ~Shape() {}
    virtual double Area() const { return 0; }
    virtual void shapeName() const = 0;
};
class Circle : public Shape
{
public:
    Circle(double r) { radius = r; }
    ~Circle() {}
    virtual double Area() const { return 3.14159 * radius * radius; }
    virtual void shapeName() const { cout << "Circle "; }

protected:
    double radius;
};
class Square : public Shape
{
public:
    Square(double a) { x = a; }
    ~Square() {}
    virtual double Area() const { return x * x; }
    virtual void shapeName() const { cout << "Square "; }

protected:
    double x;
};
class Rectangle : public Shape
{
public:
    Rectangle(double a, double b)
    {
        x = a;
        y = b;
    }
    ~Rectangle() {}
    virtual double Area() const { return x * y; }
    virtual void shapeName() const { cout << "Rectangle "; }

protected:
    double x, y;
};
class Trapezoid : public Shape
{
public:
    Trapezoid(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }
    ~Trapezoid() {}
    virtual double Area() const { return ((x + y) * z) / 2; }
    virtual void shapeName() const { cout << "Trapezoid "; }

protected:
    double x, y, z;
};
class Triangle : public Shape
{
public:
    Triangle(double a, double h)
    {
        x = a;
        y = h;
    }
    ~Triangle() {}
    virtual double Area() const { return (x * y) / 2; }
    virtual void shapeName() const { cout << "Triangle "; }

protected:
    double x, y;
};
int main()
{
    Circle circle(5);
    Square square(4);
    Rectangle rectangle(3, 4);
    Trapezoid trapezoid(2.0, 3.0, 4.0);
    Triangle triangle(4, 3);
    double sum = 0;
    Shape *pt[5] = {&circle, &square, &rectangle, &trapezoid, &triangle};
    Shape **p;
    for (p = pt; p < pt + 5; p++)
    {
        (*p)->shapeName();
        cout << "area=" << (*p)->Area() << endl;
        sum += (*p)->Area();
    }
    cout << "Area sum=" << sum << endl;
    system("pause");
    return 0;
}
