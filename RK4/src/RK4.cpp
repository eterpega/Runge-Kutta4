#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>

using std::vector;
using std::cout;
using std::endl;

class Algorithm
{
public:
	float step_size = 0.01; // Step Size Used
	float target_x = 4; // x Value of Interest
	float Solve(); // Main Algorithm
	double k1, k2, k3, k4;



	class Equation // Holds Equation-Based Data
	{
	public:
		int dimensions;
		float initial_condition; // IC @ x=0
		vector<double> x, y; // Containers for x and y
		double(*differential_equation)(double, double);
	}Eqn;

}Algo;

double MyFunction(double x, double y)
{
	double result = x + y;
	return result;
}

float Algorithm::Solve()
{
	double result;
	Eqn.x.push_back(0);
	Eqn.y.push_back(Algo.Eqn.initial_condition);
	for (int position = 0; Eqn.x.back() < target_x; ++position)
	{
		Eqn.x.push_back(Algo.Eqn.x.back() + step_size);
		k1 = step_size*Eqn.differential_equation(Eqn.x.at(position), Eqn.y.at(position));
		k2 = step_size*Eqn.differential_equation(Eqn.x.at(position) + 0.5*step_size, Eqn.y.at(position) + 0.5*k1);
		k3 = step_size*Eqn.differential_equation(Eqn.x.at(position) + 0.5*step_size, Eqn.y.at(position) + 0.5*k2);
		k4 = step_size*Eqn.differential_equation(Eqn.x.at(position) + step_size, Eqn.y.at(position) + k3);
		result = Eqn.y.back() + (1.0 / 6.0)*k1 + (1.0 / 3.0)*k2 + (1.0 / 3.0)*k3 + (1.0 / 6.0)*k4;
		Eqn.y.push_back(result);
		cout << "X: " << Algo.Eqn.x.back() << "    " << "Y: " << Algo.Eqn.y.back() << endl;
	}
	return 0;
}

int main()
{
	Algo.Eqn.initial_condition = 1;
	Algo.Eqn.differential_equation = MyFunction;
	Algo.Solve();
	system("pause");
	return 0;
}