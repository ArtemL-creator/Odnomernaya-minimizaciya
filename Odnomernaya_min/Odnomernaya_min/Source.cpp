#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

double F(double x)
{
	return pow(M_E, x) - 1 - x - pow(x, 2) / 2 - pow(x, 3) / 6;
}





pair <double, double> intSwann(double x, double t)
{
	int k = 0;
	// шаг2
	double xa = x - t;
	double xb = x + t;
	cout << "Интервал: " << "[" << xa << "; " << xb << "]" << endl;

	// шаг3
	if (F(xa) >= F(x) && F(x) <= F(xb)) { return pair <double, double>(xa, xb); } // вернуть интервал

	if (F(xa) <= F(x) && F(x) >= F(xb)) { return pair <double, double>(xa = 0, xb = 0); cout << "Введите другое значение x" << endl; } // ввести другой х

	// шаг4
	double dl = 0;
	if (F(xa) >= F(x) && F(x) >= F(xb)) { dl = t; xa = x; x = xb; k = 1; }

	if (F(xa) <= F(x) && F(x) <= F(xb)) { dl = -t; xb = x; x = xa; k = 1; }

k5:
	//шаг5
	double x1 = x + pow(2, k) * dl;
	if (k > 1) { cout << "Итерация #" << k - 2 << " а = " << xa << "; b = " << xb << endl; }
	
	//шаг6
	if ((F(x1) < F(x)) && dl == t) {

		xa = x;
		x = x1;
		k++;
		goto k5;
	}
	else if ((F(x1) < F(x)) && dl == -t) {
		
		xb = x;
		x = x1;
		k++;
		goto k5;
	}
	else if ((F(x1) >= F(x)) && dl == t) {
		xb = x1;
		cout << "Итерация #" << k - 1 << " а = " << xa << "; b = " << xb << endl; 
		return pair <double, double>(xa, xb); // выход из алгоритма, вывод [ха, хв] 
	}
	else if ((F(x1) >= F(x)) && dl == -t) {
		xa = x1;
		cout << "Итерация #" << k - 1 << " а = " << xa << "; b = " << xb << endl; 
		return pair <double, double>(xa, xb); // выход из алгоритма, вывод [ха, хв] 
	}

	
}

double Gold(pair<double,double> nint, double l)
{
	double x = 0, y = 0, z = 0, a = nint.first, b = nint.second;
	double dl = 0;

	// шаг2
	int k = -1;

	// шаг3
	y = a + ((3 - sqrt(5)) / 2) * (b - a);
	z = a + b - y;

	// шаг4-5
	k4:
	if (F(y) <= F(z)){
		b = z;
		z = y;
		y = a + b - y;	
	}
	else {
		a = y;
		y = z;
		z = a + b - z;
	}

	// шаг6
	dl = abs(b - a);
	if (dl >= l) {
		k = k + 1;
		cout << "Итерация #" << k << " : " << dl << " >= " << l << endl;
		goto k4;
	}
	else { k = k + 1; cout << "Итерация #" << k << " : " << dl << " >= " << l << endl; return (a + b) / 2; }
}

//void Sven(double x, double t, int k)
//{
//	// шаг2
//	double xa = x - t;
//	double xb = x + t;
//	cout << "Начальный интервал: " << k << " [" << xa << "; " << xb << "]" << endl;
//
//	// шаг3
//	if (F(xa) >= F(x) && F(x) <= F(xb)) { return; } // вернуть интервал
//
//	if (F(xa) <= F(x) && F(x) >= F(xb)) { return; } // ввести другой х
//
//	// шаг4
//	double dl = 0;
//	if (F(xa) >= F(x) && F(x) >= F(xb)) { dl = t; xa = x; x = xb; k = 1; }
//
//	if (F(xa) <= F(x) && F(x) <= F(xb)) { dl = -t; xb = x; x = xa; k = 1; }
//
//k5:
//	//шаг5
//	double x1 = x + pow(2, k) * dl;
//	cout << "Итерация #" << k-1 << " а = " << xa << "; в = " << xb << endl;
//	//шаг6
//	if ((F(x1) < F(x)) && dl == t) {
//
//		xa = x;
//		x = x1;
//		k++;
//		goto k5;
//	}
//	else if ((F(x1) < F(x)) && dl == -t) {
//
//		xb = x;
//		x = x1;
//		k++;
//		goto k5;
//	}
//	else if ((F(x1) >= F(x)) && dl == t) {
//		xb = x1;
//		return; // выход из алгоритма, вывод [ха, хв] 
//	}
//	else if ((F(x1) >= F(x)) && dl == -t) {
//		xa = x1;
//		return; // выход из алгоритма, вывод [ха, хв] 
//	}
//
//
//}




int main()
{
	system("chcp 1251");
	system("cls");

	double x = 5;
	double t = 0.5;
	auto nint = intSwann(x, t);
	cout << "Начальный интервал неопределенности: [" << nint.first << "; " << nint.second << "]" << endl;
	cout << "x ~ " << Gold(nint, 1) << endl;

	return 0;
}