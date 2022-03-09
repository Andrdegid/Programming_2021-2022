#include<iostream>
#include<vector>
using namespace std;

class ElPolynom 
{
protected:
	int power;
	float coef;
public:
	//конструкторы
	ElPolynom() {}
	ElPolynom(float coef_, int power_)
	{
		coef = coef_;
		power = power_;
	}

	ElPolynom(const ElPolynom& other) //конструткор копирования
	{
		coef = other.coef;
		power = other.power;
	}

	ElPolynom& operator=(const ElPolynom& other)  //оператор присванивания
	{
		this->power = other.getpower();
		this->coef = other.getcoef();
		return *this;
	}

	//геттеры
	int getpower() const
	{
		return power;
	}

	float getcoef() const
	{
		return coef;
	}

	//сеттеры
	void setpower(int power)
	{
		this->power = power;
	}

	void setcoef(float coef)
	{
		this->coef = coef;
	}

	//вывод
	void Print() const
	{
		if (power != 0 && power != 1)
			cout << coef << "x^" << power;
		else if (power == 0)
			cout << coef;
		else if (power == 1)
			cout << coef << "x";
	}

};


class Polynom : public ElPolynom
{
private:
	vector<ElPolynom> arr;
	int k;
public:
	void sumpower(vector<ElPolynom>& el) //сумма слагаемых с одинаковым показателем степени
	{
		if (el.size() > 0)
		{
			for (int i=0; i<el.size()-1;i++)
			{
				for (int j = i + 1; j < el.size(); j++)
				{
					if (el[i].getpower() == el[j].getpower())
					{
						el[i].setcoef(el[i].getcoef() + el[j].getcoef());
					}
				}

			}
		}
	}

	void sort(vector<ElPolynom>& el) //приведение полинома к стандартному виду
	{
		int j;
		ElPolynom key;
		if (el.size() > 1)
		{
			for (int i = 1; i < el.size(); i++)
			{
				key = el[i];
				j = i - 1;
				while (j >= 0 && key.getpower() > el[j].getpower())
				{
					el[j + 1] = el[j];
					j--;
				}
				el[j + 1] = key;
			}
		}
	}

	void setP(vector<ElPolynom> el)
	{
		this->arr = el;
		this->k = el.size();
		sumpower(this->arr);
		sort(this->arr);
	}

	//конструкторы
	Polynom() {};
	Polynom(vector<ElPolynom>& el)
	{
		this->k = el.size();
		setP(el);
	}

	//деструктор
	~Polynom() {};

	ElPolynom getel(int i) //возвращает элемент массива одночленов
	{
		return arr[i];
	}

	//вывод
	void Print()
	{
		arr[0].Print();
		for (int i = 1; i < arr.size(); i++)
			if (arr[i].getcoef() > 0)
			{
				cout << "+";
				arr[i].Print();
			}
			else if (arr[i].getcoef()<0)
			{
				arr[i].Print();
			}
	}

	//оператор присваивания
    Polynom& operator = (const Polynom& other)
    {
        for (int i = 0; i < this->k; i++)
            this->arr.pop_back();
        for (int i = 0; i < other.k; i++)
            this->arr.push_back(other.arr[i]);
		this->k = other.k;
        setP(this->arr);
        return *this;
    }

	//проверка на равенство
    bool operator == (Polynom& other)
    {
        if (k != other.k)
            return false;
        for (int i = 0; i < other.k; i++)
            if (arr[i].getpower() != other.getel(i).getpower() || arr[i].getcoef() != other.getel(i).getcoef())
                return false;
        return true;
    }

	//неравенство
    bool operator != (Polynom& other)
    {
        if (k != other.k)
            return true;
        for (int i = 0; i < other.k; i++)
            if (arr[i].getpower() != other.getel(i).getpower() || arr[i].getcoef() != other.getel(i).getcoef())
                return true;
        return false;
    }

	//перегрузка оператора сложения
    friend Polynom operator + (const Polynom& other1, const Polynom& other2)
    {
        vector<ElPolynom> sum;
        sum = other1.arr;
        if (other2.arr.size() > 0)
            for (int i = 0; i < other2.arr.size(); i++)
                sum.push_back(other2.arr[i]);
        return Polynom(sum);
    }

	//перегрузка оператора разности
    friend Polynom operator - (const Polynom& other1, const Polynom& other2)
    {
        vector<ElPolynom> diff = other1.arr;
        vector<ElPolynom> invertother2 = other2.arr;
        for (int i = 0; i < invertother2.size(); i++)
            invertother2[i].setcoef(-1 * invertother2[i].getcoef());
        
        if (other2.arr.size() > 0)
            for (int i = 0; i < other2.arr.size(); i++)
                diff.push_back(invertother2[i]);
        return Polynom(diff);
    }

	//перегрузка оператора +=
    Polynom operator += (Polynom& other)
    {
        *this = *this + other;
        return *this;
    }

	//перегрузка оператора -=
    Polynom operator -= (Polynom& other)
    {
        *this = *this - other;
        return *this;
    }

	//перегрузка оператора умножения
    friend Polynom operator * (Polynom& other1, Polynom& other2)
    {
        vector<ElPolynom> multy;
        for (int i = 0; i < other1.arr.size(); i++)
            for (int j = 0; j < other2.arr.size(); j++)
                multy.push_back(ElPolynom(other1.arr[i].getcoef() * other2.arr[j].getcoef(), other1.arr[i].getpower() + other2.arr[j].getpower()));
        other1.setP(multy);
        return other1;
    }

	//перегрузка оператора *=
	Polynom operator *= (Polynom& other)
	{
		*this = *this * other;
		return *this;
	}

	//перегрузка оператора деления
    friend Polynom operator / (Polynom& other, float x)
    {
        if (x!=0)
            for (int i = 0; i < other.arr.size(); i++)
                other.arr[i].setcoef((other.arr[i].getcoef()) / x);
        return other;
    }

	//перегрузка оператора /=
    Polynom operator /= (float x)
    {
        *this = *this / x;
        return *this;
    }

	//перегрузка оператора ввода 
    friend istream& operator >> (istream& cin_, Polynom& other)
    {
        int coef_, power_, ind;
		cin >> ind;
        cin_ >> coef_;
        cin_ >> power_;
        other.arr[ind] = ElPolynom(coef_, power_);
        other.setP(other.arr);
        return cin_;
    }

	//перегрузка опертора вывода
    friend ostream& operator << (ostream& cout_, Polynom& other)
    {
		int ind;
		cin >> ind;
		cout_ << other.arr[ind].getcoef() << "  " << other.arr[ind].getpower() << endl;
		return cout_;
    }

	//перегрузка оператора []
    ElPolynom operator [] (int i)
    {
        return this->arr[i];
    }

};

int main()
{
	ElPolynom ep11(1, 2), ep12(3, 4), ep13(2, 3);
	ElPolynom ep21(4, 5), ep22(5, 0), ep23(0, 1);
	vector<ElPolynom> arr1, arr2;
	arr1 = { ep11, ep12, ep13 };
	arr2 = { ep21, ep22, ep23 };
	Polynom pol1(arr1), pol2(arr2), pol3;

	//вывод полиномов
	pol1.Print();
	cout << endl;
	pol2.Print();
	cout << endl << endl;

	//сумма полиномов
	pol3 = pol1 + pol2;
	pol3.Print();
	cout << endl << endl;

	//разность полиномов
	pol3 = pol1 - pol2;
	pol3.Print();
	cout << endl << endl;

	//умножение полиномов
	pol3 = pol1 * pol2;
	pol3.Print();
	cout << endl << endl;

	//деление полинома на число
	float x = 2;
	pol3 = pol3 / x;
	pol3.Print();
	cout << endl << endl;

	return 0;
}