#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;
#include <fstream>
int main(){


	double a, b, c;
	cin >> a >> b >> c;
	double d = b*b - 4 * a*c;
	if (d < 0){
		cout << "no solutions\n";
		return 0;
	}
	if (d == 0){
		cout << "one solution\n";
		printf("%.7lf", -b / (2 * a));
		return 0;
	}
	cout << "two solutions\n";
	printf("%.7f\n", (-b + sqrt(d)) / (2 * a));
	printf("%.7lf", (-b - sqrt(d)) / (2 * a));


std::ofstream out("fdf.out");
out << a << " " << b << " " << c <<"\n";

	return 0;
}
