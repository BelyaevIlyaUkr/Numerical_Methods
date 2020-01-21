#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES


#include <iostream>

using namespace std;

double equation_solution(double x) {
	return 2 * pow(M_E, 0.5 * x);
}

double Second_Derivative(double y, double First_Derivative) {
	return (First_Derivative * First_Derivative) / y;
};

double RungeKutte(double h, double a, double b) {
	double k1, k2, k3, k4;
	double s1, s2, s3, s4;
	double y = 2.;
	double First_Derivative = 1.;
	double x = a;

	while (x < b) {
		s1 = h * First_Derivative;
		k1 = h * Second_Derivative(y, First_Derivative);
		s2 = h * (First_Derivative + k1 / 2);
		k2 = h * Second_Derivative(y + s1 / 2, First_Derivative + k1 / 2);
		s3 = h * (First_Derivative + k2 / 2);
		k3 = h * Second_Derivative(y + s2 / 2, First_Derivative + k2 / 2);
		k4 = h * Second_Derivative(y + s3, First_Derivative + k3);
		s4 = h * (First_Derivative + k3);
		x = x + h;
		First_Derivative = First_Derivative + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
		y = y + (s1 + 2 * s2 + 2 * s3 + s4) / 6.0;
	}

	return y;
}

void Task1(double a, double b, double eps) {

	double h = (b - a) / 10;
	double primary_solution = equation_solution(b);
	double deflection = 10;

	while (deflection > eps) {
		h = h / 2;
		deflection = fabs(primary_solution - RungeKutte(h, a, b));
	}

	cout << "\tTask 1\n";
	printf("b=%.1lf\ny= %lf\n", b, RungeKutte(h, a, b));
	printf("h = %.4lf\n", h);
	printf("error = %.7lf\n\n", deflection);
}

void Task2(double a, double b, double eps) {
	double hNew = sqrt(sqrt(eps));

	double yOld;

	double yNew = RungeKutte(hNew, a, b);
	int iterations = 0;

	do {
		if (iterations > 5000) {
			cout << "Max iteration was reached\n";
			break;
		}
		yOld = yNew;
		hNew = hNew / 2;
		yNew = RungeKutte(hNew, a, b);
		iterations++;
	} while (fabs(yOld - yNew) > eps);

	cout << "\tTask 2\n";

	printf("h = %.4lf\n\n", hNew);
}

void Task3(double a, double b, double eps) {

	double h = (b - a) / 10;

	cout << "\tTask 3\n";
	cout << "-------------------------------------------\n";

	printf("|    x    |       y       |    delta      |\n");

	cout << "-------------------------------------------\n";

	double x = a;

	while (x <= b) {
		double value = RungeKutte(h, a, x);

		printf("| %7.2lf | %13.4e | %13.4e |\n", x, value, fabs(equation_solution(x) - value));
		printf("-------------------------------------------\n");

		x += h;
	}

}


int main() {

	double a = 0.;
	double b = 2.;
	double eps = 1e-2;

	Task1(a, b, eps);

	Task2(a, b, eps);

	Task3(a, b, eps);

	system("pause");

	return 0;
}
