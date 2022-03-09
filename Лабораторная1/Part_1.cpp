#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

class Point
{
private:
    float x, y;
public:
    //конструкторы
    Point()
    {
        x = 0;
        y = 0;
    }
    Point(float x_, float y_)
    {
        x = x_;
        y = y_;
    }

    Point(const Point& other) //конструктор копирования
    {
        x = other.x;
        y = other.y;
    }

    Point& operator = (const Point& other) //оператор присваивания
    {
        x = other.getx();
        y = other.gety();
        return*this;
    }

    void Print() //вывод
    {
        cout << "X = " << this->x << "   " << "Y = " << this->y << endl;
    }

    float getx(void) const
    {
        return x;
    }

    float gety() const
    {
        return y;
    }

    void setx(float x)
    {
        this->x = x;
    }

    void sety(float y)
    {
        this->y = y;
    }

};

class Broken
{
protected:
    float dist(Point& a, Point& b) //функция считает рассотояние от точки до точки
    {
        return sqrt(pow(a.getx() - b.getx(), 2) + pow(a.gety() - b.gety(), 2));
    }
    vector<Point> masP;
    int k;
public:
    //конструкторы
    Broken()
    {
        k = 0;
    }

    Broken(vector<Point>& mas, int k)
    {
        this->k = k;
        for (int i = 0; i < k; i++)
            masP.push_back(mas[i]);
    }

    Broken(const Broken& other) //конструктор копирования
    {
        k = other.k;
        for (int i = 0; i < k; i++)
            masP[i] = other.masP[i];
    }

    Broken& operator = (const Broken& other) //оператор присваивания
    {
        for (int i = 0; i < this->k; i++)
            this->masP.pop_back();
        for (int i = 0; i < other.k; i++)
            this->masP.push_back(other.masP[i]);
        this->k = other.k;
        return *this;
    }

    virtual float getl()
    {
        float l = 0;
        for (int i = 0; i < this->masP.size() - 1; i++)
            l += dist(this->masP[i], this->masP[i + 1]);
        return l;
    }

    virtual void Print() //вывод
    {
        for (int i = 0; i < masP.size(); i++)
            cout << "X" << i << " = " << masP[i].getx() << "   " << "Y" << i << " = " << masP[i].gety() << endl;
    }
};

class ClosedBroken : public Broken
{
public:
    //конструкторы
    ClosedBroken() : Broken() {};
    ClosedBroken(vector<Point>& mas, int k) : Broken(mas, k) {};

    ClosedBroken(const ClosedBroken& other) : Broken(other) {}; //конструткор копирования

    ClosedBroken& operator = (const ClosedBroken& other) //оператор присваивания
    {
        for (int i = 0; i < this->k; i++)
            this->masP.pop_back();
        for (int i = 0; i < other.k; i++)
            this->masP.push_back(other.masP[i]);
        this->k = other.k;
        return *this;
    }

    virtual float getl()
    {
        float l = Broken::getl();
        l += dist(masP[0], masP[masP.size() - 1]);
        return l;
    }
};

class Polygon : public ClosedBroken
{
public:
    //конструкторы
    Polygon() : ClosedBroken() {};
    Polygon(vector<Point>& mas, int k) : ClosedBroken(mas, k) {};

    Polygon(const Polygon& other) : ClosedBroken(other) {}; //конструткор копирования

    Polygon& operator = (const Polygon& other) //оператор присваивания
    {
        for (int i = 0; i < this->k; i++)
            this->masP.pop_back();
        for (int i = 0; i < other.k; i++)
            this->masP.push_back(other.masP[i]);
        this->k = other.k;
        return *this;
    }

    virtual float Perimetr() //функция для расчёта периметра
    {
        float P = ClosedBroken::getl();
        return P;
    }

    virtual float Square() //функция для расчёта площади
    {
        float p1 = 0, p2 = 0, S = 0;
        for (int i = 0; i < masP.size() - 1; i++)
        {
            p1 += masP[i].getx() * masP[i + 1].gety();
            p2 += masP[i].gety() * masP[i + 1].getx();
        }
        p1 += masP[masP.size() - 1].getx() * masP[0].gety();
        p2 += masP[masP.size() - 1].gety() * masP[0].getx();
        S = abs((p1 - p2) / 2);
        return S;
    }
};

class Triangle : public Polygon
{
public:
    //конструкторы
    Triangle() : Polygon() {};
    Triangle(vector<Point>& mas, int k) : Polygon(mas, k) {};

    Triangle(const Triangle& other) : Polygon(other) {}; //конструткор копирования

    Triangle& operator = (const Triangle& other) //оператор присваивания
    {
        for (int i = 0; i < this->k; i++)
            this->masP.pop_back();
        for (int i = 0; i < other.k; i++)
            this->masP.push_back(other.masP[i]);
        this->k = other.k;
        return *this;
    }

    bool Check() //проверка: лежат ли 3 точки на одной прямой
    {
        if (this->k==3 && masP.size() == 3 && ((masP[2].getx() - masP[0].getx()) * (masP[1].gety() - masP[0].gety()) != (masP[2].gety() - masP[0].gety()) * (masP[1].getx() - masP[0].getx())))
            return true;
        else
            return false;
    }

};

class Trapezoid : public Polygon
{
public:
    //конструкторы
    Trapezoid() : Polygon() {};
    Trapezoid(vector<Point>& mas, int k) : Polygon(mas, 4) {};

    Trapezoid(const Trapezoid& other) : Polygon(other) {}; //конструткор копирования

    Trapezoid& operator = (const Trapezoid& other) //оператор присваивания
    {
        for (int i = 0; i < this->k; i++)
            this->masP.pop_back();
        for (int i = 0; i < other.k; i++)
            this->masP.push_back(other.masP[i]);
        this->k = other.k;
        return *this;
    }

    bool checkTrapezoid() //проверка на параллельность сторон
    {
        vector<int> kx(4);
        vector<int> ky(4);
        for (int i = 3; i > 0; i--)
        {
            kx[i] = masP[i].getx() - masP[i - 1].getx();
            ky[i] = masP[i].gety() - masP[i - 1].gety();
        }
        kx[0] = masP[3].getx() - masP[0].getx();
        ky[0] = masP[3].gety() - masP[0].gety();
        if ((masP.size() == 4 && this->k == 4) && ((ky[0] / kx[0] == ky[2] / kx[2]) && (ky[1] / kx[1] != ky[3] / kx[3])) || ((ky[0] / kx[0] != ky[2] / kx[2]) && (ky[1] / kx[1] == ky[3] / kx[3])))
            return true;
        else
            return false;
    }
};

class RegularPolygon : public Polygon
{
public:
    //конструкторы
    RegularPolygon() : Polygon() {};
    RegularPolygon(vector<Point>& mas, int k) : Polygon(mas, k) {};

    RegularPolygon(const RegularPolygon& other) : Polygon(other) {}; //конструткор копирования

    RegularPolygon& operator = (const RegularPolygon& other) //оператор присваивания
    {
        for (int i = 0; i < this->k; i++)
            this->masP.pop_back();
        for (int i = 0; i < other.k; i++)
            this->masP.push_back(other.masP[i]);
        this->k = other.k;
        return *this;
    }
    bool checkRegularPolygon() //проверка на равенство сторон и углов
    {
        float y, dl, flag = 0;
        float kx1 = masP[1].getx() - masP[0].getx(), kx2 = masP[0].getx() - masP[masP.size() - 1].getx();
        float ky1 = masP[1].gety() - masP[0].gety(), ky2 = masP[0].gety() - masP[masP.size() - 1].gety();
        float standarty = acos((abs(kx1 * kx2 + ky1 * ky2)) / (abs(dist(masP[0], masP[masP.size() - 1])) * abs(dist(masP[0], masP[1]))));
        float standdl = dist(masP[0], masP[masP.size() - 1]);
        for (int i = 0; i < masP.size() - 3; i++)
        {
            kx1 = masP[i + 1].getx() - masP[i].getx();
            kx2 = masP[i + 2].getx() - masP[i + 1].getx();
            ky1 = masP[i + 1].gety() - masP[i].gety();
            ky2 = masP[i + 2].gety() - masP[i + 1].gety();
            y = acos((abs(kx1 * kx2 + ky1 * ky2)) / (abs(dist(masP[i], masP[i+1])) * abs(dist(masP[i+1], masP[i+2]))));
            dl = dist(masP[i], masP[i + 1]);
            if (y != standarty || dl != standdl)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            return true;
        else
            return false;
    }
};

int main()
{
    //проверка класса Point
    Point A;
    Point B;
    Point C(3, 4);
    A = C;
    A = B = C;
    A.Print();
    B.Print();
    C.Print();
    cout << endl << endl;

    //проверка класса Broken
    vector<Point> t;
    Point A1(1, 2);
    Point B1(3, 4);
    Point C1(5, 2);
    t.push_back(A1);
    t.push_back(B1);
    t.push_back(C1);
    Broken r(t, 3);
    cout << r.getl() << endl;
    Broken p;
    p = r;
    p.Print();
    cout << endl << endl;

    //проверка класса ClosedBroken
    t.push_back(A1);
    ClosedBroken cb(t, 4);
    cout << cb.getl() << endl;
    ClosedBroken cb1;
    cb1 = cb;
    cb1.Print();
    t.pop_back();
    cout << endl << endl;

    //проверка класса Polygon
    Point D1(3, 0);
    t.push_back(D1);
    Polygon pol(t, 4);
    cout << pol.Perimetr() << "   " << pol.Square() << endl;
    Polygon pol1;
    pol1 = pol;
    pol1.Print();
    cout << endl << endl;

    //проверка класса Triangle
    t.pop_back();
    Triangle tr(t, 3);
    cout << tr.Perimetr() << "   " << tr.Square() << endl;
    cout << tr.Check() << endl;
    Triangle tr1;
    tr1 = tr;
    tr1.Print();
    cout << endl << endl;

    //проверка класса Trapezoid
    t.pop_back();
    Point D2(4, 4);
    t.push_back(D2);
    t.push_back(C1);
    Trapezoid trap(t, 4);
    cout << trap.Perimetr() << "   " << trap.Square() << endl;
    cout << trap.checkTrapezoid() << endl;
    Trapezoid trap1;
    trap1 = trap;
    trap1.Print();
    cout << endl << endl;

    //проверка класса RegularPolygon
    t.pop_back();
    t.pop_back();
    t.push_back(C1);
    t.push_back(D1);
    RegularPolygon rp(t, 4);
    cout << rp.Perimetr() << "   " << rp.Square() << endl;
    cout << rp.checkRegularPolygon() << endl;
    RegularPolygon rp1;
    rp1 = rp;
    rp1.Print();
    cout << endl;
    Point Zero(0, 0);
    t.push_back(Zero);
    RegularPolygon rp2(t, 5);
    cout << rp2.checkRegularPolygon() << endl;

    return 0;
}