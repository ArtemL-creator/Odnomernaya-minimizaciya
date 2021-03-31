#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

double F(double x)
{
	return pow(M_E, x) - 1 - x - pow(x, 2) / 2 - pow(x, 3) / 6;
}


double KvdInt(double x1, double dl, double eps1, double eps2)
{
	double xl = 0;
	double fxl = 0;
	double fm = 0;
	double xm = 0;
	double x3 = 0;
	int k = -1;
	k2:
	// ���2
	double x2 = x1 + dl;

	// ���3
	double f1 = F(x1);
	double f2 = F(x2);

	// ���4
	if (f1 > f2) {
		x3 = x1 + 2 * dl;
	}
	else {
		x3 = x1 - dl;
	}

	 // ���5
	double f3 = F(x3);

	k6:
	// ���6
	if ((f1 < f2) && (f2 < f3)) {
		fm = f1;
		xm = x1;
	}
	else if ((f2 < f1) && (f1 < f3)) {
		fm = f2;
		xm = x2;
	}
	else {
		fm = f3;
		xm = x3;
	}

	// ���7
	if (((x2 - x3) * f1 + (x3 - x1) * f2 + (x1 - x2) * f3) == 0) {
		x1 = xm;
		k++;
		cout << "�������� #" << k << " : " << " x1 := xmin " << endl;
		goto k2;
	}
	else {

		xl = (((x2 * x2 - x3 * x3) * f1 + (x3 * x3 - x1 * x1) * f2 + (x1 * x1 - x2 * x2) * f3) / ((x2 - x3) * f1 + (x3 - x1) * f2 + (x1 - x2) * f3)) / 2;
		fxl = F(xl);
	}

	// ���8
	if ((abs((fm - fxl) / fxl) < eps1) && ((abs((xm - xl) / xl)) < eps2)) {
		return xl;
	}
	else if ((x1 < xl) && (xl < x3)) {
		if (fm < fxl) {
			if (xm < x2) {
				x3 = x2;
				x2 = xm;
				k++;
			}
			else {
				x2 = xm;
				k++;
			}
		}
		else {
			if (xl < x2) {
				x3 = x2;
				x2 = xl;
				k++;
			}
			else {
				x2 = xl;
				k++;
			}
		}
		goto k6;
	}
	else {
		x1 = xl;
		k++;
		cout << "�������� #" << k << " : " << " x1 := x^ " << endl;
		goto k2;
	}

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



int main()
{
	system("chcp 1251");
	system("cls");


	bool f = true;
	do {
		short k = 0;
		cout << " ��� ������� f(x) = e^x - 1 - x - (x^2)/2 - (x^3)/6 : " << endl;
		cout << " 1. � ������� ��������� ����� ����� ��������� �������� ����������������� (����� ��������� ����� �������� ������� ��� ���������� ���������)" << endl;
		cout << " 2. ��������� ����� �������� �������" << endl;
		cout << " 3. ��������� ����� ������������ ������������" << endl ;
		cout << " 0. �����" << endl;
		cout << " ������� 0, 1, 2 ��� 3: ";
		cin >> k;
		system("cls");

		pair <double, double> nint;
		pair <double, double> nint1;
		short fo = 0;
		short fo1 = 0;
		short fo2 = 0;
		short fg = 0;

		switch (k)
		{
		case 1:
			cout << " ������� ��������� �����:" << endl;
			double x;
			cout << "x = ";
			cin >> x;
			cout << " ������� �������� ����:" << endl;
			double t;
			cout << "t = ";
			cin >> t;
			nint = intSwann(x, t);
			cout << "��������� �������� ����������������: [" << nint.first << "; " << nint.second << "]" << endl << endl;
			cout << " ������������ ���� �������� � ������ �������� �������? 1. �� 2. ���:";
			
			do {
				cin >> fg;
				if (fg == 1) {
					double l;
					cout << " ������� ��������: " << endl;
					cout << "l = ";
					cin >> l;
					cout << "x ~ " << Gold(nint, l) << endl << endl;
					break;
				}
				else if (fg == 2) {
					cout << endl;
					break;
				}
			} while (fg == 1 || fg == 2);
			
			cout << " �������� ������� � ����������? 1. ��: ";
			
			do {
				cin >> fo;
				if (fo == 1) {
					system("cls");
				}
			} while (fo != 1);
			break;

		case 2:
			cout << " ������� ��������� �������� ����������������: ";
			double a;
			double b;
			cout << "a = ";
			cin >> a;
			cout << "b = ";
			cin >> b;
			double l1;
			cout << " ������� ��������: " << endl;
			cout << "l = ";
			cin >> l1;
			cout << "x ~ " << Gold(nint1, l1) << endl << endl;

			cout << " �������� ������� � ����������? 1. ��: ";
			do {
				cin >> fo1;
				if (fo1 == 1) {
					system("cls");
				}
			} while (fo1 != 1);
			break;

		case 3:
			cout << " ������� ��������� �����:" << endl;
			double x2;
			cout << "x = ";
			cin >> x2;
			cout << " ������� �������� ����:" << endl;
			double dl;
			cout << "dl = ";
			cin >> dl;
			cout << " ������� ����������� ��� �������:" << endl;
			double eps1;
			cout << "eps1 = ";
			cin >> eps1;
			cout << " ������� ����������� ��� �����:" << endl;
			double eps2;
			cout << "eps2 = ";
			cin >> eps2;
			system("cls");

			cout << "x = " << x2 << "dl = " << dl << "eps1 = " << eps1 << "eps2 = " << eps2 << endl;
			cout << " x ~ " << KvdInt(x2, dl, eps1, eps2) << endl;
			
			cout << " �������� ������� � ����������? 1. ��: ";
			do {
				cin >> fo2;
				if (fo2 == 1) {
					system("cls");
				}
			} while (fo2 != 1);
		break;
		case 0:
			system("cls");
			f = false;
			break;
		}

	} while (f);


//	double x = 5;
//	double t = 0.5;
//	cout << "x ~ " << Gold(nint, 1) << endl;
//cout << " x ~~ " << KvdInt(1, 1, 1, 1) << endl;
	return 0;
}