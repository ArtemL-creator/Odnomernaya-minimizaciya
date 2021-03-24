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
	// ���2
	double xa = x - t;
	double xb = x + t;
	cout << "��������: " << "[" << xa << "; " << xb << "]" << endl;

	// ���3
	if (F(xa) >= F(x) && F(x) <= F(xb)) { return pair <double, double>(xa, xb); } // ������� ��������

	if (F(xa) <= F(x) && F(x) >= F(xb)) { return pair <double, double>(xa = 0, xb = 0); cout << "������� ������ �������� x" << endl; } // ������ ������ �

	// ���4
	double dl = 0;
	if (F(xa) >= F(x) && F(x) >= F(xb)) { dl = t; xa = x; x = xb; k = 1; }

	if (F(xa) <= F(x) && F(x) <= F(xb)) { dl = -t; xb = x; x = xa; k = 1; }

k5:
	//���5
	double x1 = x + pow(2, k) * dl;
	if (k > 1) { cout << "�������� #" << k - 2 << " � = " << xa << "; b = " << xb << endl; }
	
	//���6
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
		cout << "�������� #" << k - 1 << " � = " << xa << "; b = " << xb << endl; 
		return pair <double, double>(xa, xb); // ����� �� ���������, ����� [��, ��] 
	}
	else if ((F(x1) >= F(x)) && dl == -t) {
		xa = x1;
		cout << "�������� #" << k - 1 << " � = " << xa << "; b = " << xb << endl; 
		return pair <double, double>(xa, xb); // ����� �� ���������, ����� [��, ��] 
	}

	
}

double Gold(pair<double,double> nint, double l)
{
	double x = 0, y = 0, z = 0, a = nint.first, b = nint.second;
	double dl = 0;

	// ���2
	int k = -1;

	// ���3
	y = a + ((3 - sqrt(5)) / 2) * (b - a);
	z = a + b - y;

	// ���4-5
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

	// ���6
	dl = abs(b - a);
	if (dl >= l) {
		k = k + 1;
		cout << "�������� #" << k << " : " << dl << " >= " << l << endl;
		goto k4;
	}
	else { k = k + 1; cout << "�������� #" << k << " : " << dl << " >= " << l << endl; return (a + b) / 2; }
}

//void Sven(double x, double t, int k)
//{
//	// ���2
//	double xa = x - t;
//	double xb = x + t;
//	cout << "��������� ��������: " << k << " [" << xa << "; " << xb << "]" << endl;
//
//	// ���3
//	if (F(xa) >= F(x) && F(x) <= F(xb)) { return; } // ������� ��������
//
//	if (F(xa) <= F(x) && F(x) >= F(xb)) { return; } // ������ ������ �
//
//	// ���4
//	double dl = 0;
//	if (F(xa) >= F(x) && F(x) >= F(xb)) { dl = t; xa = x; x = xb; k = 1; }
//
//	if (F(xa) <= F(x) && F(x) <= F(xb)) { dl = -t; xb = x; x = xa; k = 1; }
//
//k5:
//	//���5
//	double x1 = x + pow(2, k) * dl;
//	cout << "�������� #" << k-1 << " � = " << xa << "; � = " << xb << endl;
//	//���6
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
//		return; // ����� �� ���������, ����� [��, ��] 
//	}
//	else if ((F(x1) >= F(x)) && dl == -t) {
//		xa = x1;
//		return; // ����� �� ���������, ����� [��, ��] 
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
	cout << "��������� �������� ����������������: [" << nint.first << "; " << nint.second << "]" << endl;
	cout << "x ~ " << Gold(nint, 1) << endl;

	return 0;
}