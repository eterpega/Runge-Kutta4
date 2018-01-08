// 3-8 Method.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <memory>
#include <functional>

using std::vector;
using std::cout;
using std::endl;


double MyFunction(double x, double y);


class Algorithm
{
public:
	virtual float Solve()=0; // Main Algorithm
	Algorithm()
	{
		step_size = 0;
		target_x = 0;
	};
	virtual void SetIC()=0;
	void FillX();

	class Equation // Holds Equation-Based Data
	{
	public:
		int dimensions;
		float initial_condition; // IC @ x=0
		vector<double> x, y; // Containers for x and y
		std::function<double(double, double)> MyFunction;
	}Eqn;

protected:
	float step_size; // Step Size Used
	float target_x; // x Value of Interest
	float initial_condition;
};
void Algorithm::FillX()
{
	for (double i = 0; i <= target_x ; i+= step_size)
	{
		Eqn.x.push_back(i);
	}
}


class RK38 : public Algorithm
{
public:
	RK38(float step, float final_x, float IC);
	float Solve();
	void SetIC();
private:

	double k1, k2, k3, k4;
};
RK38::RK38(float step, float final_x, float IC)
{
	step_size = step;
	target_x = final_x;
	initial_condition = IC;
};
void RK38::SetIC()
{
	Eqn.y.push_back(initial_condition);
}
float RK38::Solve()
{
	SetIC();
	FillX();
	for (auto i = 1; i< target_x; ++i)
	{
		k1 = step_size*Eqn.differential_equation(Eqn.x.at(i - 1), Eqn.y.at(i - 1));
		k2 = step_size*Eqn.differential_equation(Eqn.x.at(i - 1)+(step_size/3), Eqn.y.at(i - 1)+(k1/3.0));
		k3 = step_size*Eqn.differential_equation(Eqn.x.at(i - 1) + (2 * step_size) / 3.0, Eqn.y.at(i - 1) - (k1 / 3.0) + k2);
		k4 = step_size*Eqn.differential_equation(Eqn.x.at(i - 1)+step_size, Eqn.y.at(i - 1)+k1-k2+k3);
		Eqn.y.push_back(Eqn.y.at(i - 1) + (1.0 / 8.0)*(k1 + 3 * k2 + 3 * k3 + k4));
	}

	return 0;
}
double MyFunction(double x, double y)
{
	double result = x + y;
	return result;
}

int main()
{
    auto RK = std::make_shared<RK38>(1.1, 10, 2);
    RK->Eqn = MyFunction;
	RK->Solve();
    return 0;
}

