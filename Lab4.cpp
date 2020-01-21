// LAB4NumMet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

double integral(long int n, double a, double b) {
	double x_part = a;
	double result = 0;
	double h = (b - a) / n;

	for (int i = 0; i <= n; i++) {

		double y_part = 1 / x_part;
		if (!((i == 0) || (i == n)))
			y_part *= 2;
		result += y_part;
		x_part += h;
	}

	result *= h / 2;

	return result;
}

double first_task(double eps, double a, double b) {
	if (eps < 1e-16) {
		cout << "Too small eps\n";
		return -1;
	}
	double h = sqrt(12 * eps / ((b - a) * 2));
	long int n = ceil((b - a) / h);

	double result = integral(n, a, b);

	double error = fabs(log(b) - log(a) - result);

	cout << "--------------------------------------------------------------------------------------\n";
	cout << "|      eps      |      step      |      accurate value      |      result error      |\n";
	cout << "--------------------------------------------------------------------------------------\n";
	cout << "|    " << eps << "\t|  " << (b - a) / n << "\t |\t" << log(b) - log(a) << "\t\t    |\t " << error << "\t     |\n";
	cout << "--------------------------------------------------------------------------------------\n";

	return error;
}

void second_task(double eps, double a, double b) {
	if (eps < 1e-16) {
		cout << "Too small eps\n";
		return;
	}
	long int n = ceil((b-a) / sqrt(eps));
	double R = 0;
	double result;

	do {
		result = integral(2 * n, a, b);
		R = fabs(integral(n, a, b) - result) / 3;
		n *= 2;
	} while (R > eps);

	double error = fabs(log(b) - log(a) - result);

	cout << "---------------------------------------------------------------------------------\n";
	cout << "|         eps           |        step           |         result error          |\n";
	cout << "---------------------------------------------------------------------------------\n";
	cout << "|\t" << eps << "\t|\t" << (b - a) / n << "\t|\t" << error << "\t\t|\n";
	cout << "---------------------------------------------------------------------------------\n";
}
int main()
{
	second_task(first_task(1e-9, 1, 10), 1, 10);
	system("pause");
}


