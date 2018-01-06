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
		float step_size=0.01; // Step Size Used
		float target_x=4; // x Value of Interest
		float Solve(); // Main Algorithm
		
		 class Equation // Holds Equation-Based Data
		{
		public:
			 int dimensions;
			 float initial_condition; // IC @ x=0
			 vector<float> x, y; // Containers for x and y
			 float (*differential_equation)(float);

	
		}Eqn;
	}Algo;


	float Algorithm::Solve()
	{
		cout << "Solving..." << endl;
		Algo.Eqn.x.push_back(0);
		Algo.Eqn.y.push_back(Algo.Eqn.initial_condition);
		while (Algo.Eqn.x.back() < target_x)
		{
			Algo.Eqn.x.push_back(Algo.Eqn.x.back() + step_size);
			Algo.Eqn.y.push_back(Algo.Eqn.y.back() +step_size*Eqn.differential_equation(Algo.Eqn.y.back()));
			cout << "X: " << Algo.Eqn.x.back() << "    " << "Y: " << Algo.Eqn.y.back() << endl;
		}
		return 0;
	}

	
	float MyFunction(float x)
	{
		float y =x;
		return y;
	}


int main()
{
	Algo.Eqn.initial_condition = 1;
	Algo.Eqn.differential_equation = MyFunction;
	Algo.Solve();
	system("pause");
    return 0;
}






