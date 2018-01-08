#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <functional>

using std::vector;
using std::cout;
using std::endl;

class Algorithm
{
public:

    // Holds the RK4 algorithm. Call to solve the differential equation
	void Solve();

    // Variables used in the RK4 method
    double k1, k2, k3, k4;
    
    // Step size used when icreasing x
    double stepSize = 0.01; 

    // The x value that we are intersted in
    double target_x = 4; 

	struct Equation // Holds Equation-Based Data
	{
        std::function<double(double, double)> differentialEquation;

        // IC @ x=0
		float initial_condition; 

        // Containers for x and y
        vector<double> x;
        vector<double> y;
	}Eqn;

}Algo;

double MyFunction(double x, double y)
{
	return x+y;
}

void Algorithm::Solve()
{
	double result;

    // The length of the x and y vectors
    auto xYLength= target_x + 1;
    Eqn.x.reserve(xYLength);
    Eqn.y.reserve(xYLength);

    // Insert the initial condition
    Eqn.x.push_back(0);
	Eqn.y.push_back(Algo.Eqn.initial_condition);

	for (auto position = 0; Eqn.x.back() < target_x; ++position)
	{
		Eqn.x.push_back(Algo.Eqn.x.back() + stepSize);
		k1 = stepSize*(Eqn.differentialEquation(Eqn.x.at(position), Eqn.y.at(position)));
		k2 = stepSize*Eqn.differentialEquation(Eqn.x.at(position) + 0.5*stepSize, Eqn.y.at(position) + 0.5*k1);
		k3 = stepSize*Eqn.differentialEquation(Eqn.x.at(position) + 0.5*stepSize, Eqn.y.at(position) + 0.5*k2);
		k4 = stepSize*Eqn.differentialEquation(Eqn.x.at(position) + stepSize, Eqn.y.at(position) + k3);
		result = Eqn.y.back() + (1.0 / 6.0)*k1 + (1.0 / 3.0)*k2 + (1.0 / 3.0)*k3 + (1.0 / 6.0)*k4;
		Eqn.y.push_back(result);
		cout << "X: " << Algo.Eqn.x.back() << "    " << "Y: " << Algo.Eqn.y.back() << endl;
	}
}

int main()
{
    std::clock_t begin = std::clock();

    // Set the y value at x=0
	Algo.Eqn.initial_condition = 1;

    // Assign the differential equation to your function
	Algo.Eqn.differentialEquation = MyFunction;

    // Solve the equation
	Algo.Solve();

    std::cout << "Elapsed time:" << static_cast<double>(std::clock() - begin) / CLOCKS_PER_SEC << std::endl;
	system("pause");
	return 0;
}