#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>

using std::vector;
using std::cout;
using std::endl;


double MyFunction(double x, double y);


class Algorithm
{
public:
	virtual float Solve() = 0;
	Algorithm()
	{
		step_size = 0;
		target_x = 0;
	};
	void FillX();

	class Equation
	{
	public:
		int dimensions;
		float initial_condition;
		vector<double> x, y; 
		double(*differential_equation)(double, double) = MyFunction;
	}Eqn;

protected:
	float step_size; // Step Size Used
	float target_x; // x Value of Interest
	float initial_condition;
};
void Algorithm::FillX()
{
	for (double i = 0; i <= target_x; i += step_size)
	{
		Eqn.x.push_back(i);
	}
}


class RK45 : public Algorithm
{
public:
	RK45(float step, float final_x, float IC);
	float Solve();
private:
	void CalculateStepSize(double,double);
	double k1, k2, k3, k4, k5, k6;
	bool flag;
};
RK45::RK45(float step, float final_x, float IC)
{
	step_size = step;
	target_x = final_x;
	initial_condition = IC;
	Eqn.y.push_back(initial_condition);
	Eqn.x.push_back(0);
};




float RK45::Solve()
{
	double temp_y;
	double temp_x=0;
	double position = 1;
	for (auto i = 1; Eqn.x.back()< target_x; ++i)
	{

		k1 = step_size*Eqn.differential_equation(Eqn.x.at(position -1), Eqn.y.at(position -1));
		k2 = step_size*Eqn.differential_equation(Eqn.x.at(position -1) + (step_size / 4), Eqn.y.at(position -1) + (k1 / 4.0));
		k3 = step_size*Eqn.differential_equation(Eqn.x.at(position -1) + 3.0*(this->step_size / 8.0), Eqn.y.at(position -1) + (3.0*k1 / 32.0) + k2*(9.0 / 32.0));
		k4 = step_size*Eqn.differential_equation(Eqn.x.at(position -1) + step_size, Eqn.y.at(position -1) + (1932.0 / 2197.0)*k1 - (7200 / 2197)*k2 + (7296 / 2197)*k3);
		k5 = step_size*Eqn.differential_equation(Eqn.x.at(position -1) + step_size, Eqn.y.at(position -1) + (439 / 216)*k1 - (8.0*k2) + (3680.0 / 513.0)*k3 - (845 / 4104)*k4);
		k6 = step_size*Eqn.differential_equation(Eqn.x.at(position -1) + 0.5*step_size, Eqn.y.at(position -1) - (8.0 / 27)*k1 + 2.0*k2 - (3544 / 2565)*k3 + (1859 / 4104)*k4 - (11.0 / 40.0)*k5);
		temp_y = Eqn.y.at(position - 1) + (16.0 / 135.0)*k1 + (6656.0 / 12825.0)*k3 + (28561.0 / 56430.0)*k4 - (9.0 / 50.0)*k5 + (2.0 / 55.0)*k6;

		if (flag == false)
		{
			temp_x += step_size;
			this->Eqn.x.push_back(temp_x);
			CalculateStepSize(temp_y, temp_x);
			Eqn.y.push_back(temp_y);
		}
		else
		{
			Eqn.y.pop_back();
			Eqn.y.push_back(temp_y);			
			flag = false;
			position++;
		}
	}
	return 0;
}


void RK45::CalculateStepSize(double t_y, double t_x)
{
	double s;
	s = 0.84*pow(step_size / (2.0 * abs((t_x - t_y))), 0.25);
	if (s*Eqn.x.back() < 1)
		step_size = s*t_x;
	flag = 1;
}

double MyFunction(double x, double y)
{
	double result = x + y;
	return result;
}

int main()
{
	Algorithm *RK = new RK45(1.0, 10, 2);
	RK->Solve();
	return 0;
}

