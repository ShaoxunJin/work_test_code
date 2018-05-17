#include "stdafx.h"
#include "model_search.h"


int e[2][2] = {{1,0},{0,1}};

double MODEL_SEARCH_calculate_Y(xx_vect x_init, double sigma, int cycle)
{
	function_in(__FUNCTION__);
	
	xx_vect y_value[2] = {{},{}};
	xx_vect y_value_plus = {};
	xx_vect y_value_minus = {};
	y_value[0].x1 = x_init.x1 + sigma * e[0][0];
	y_value[0].x2 = x_init.x2 + sigma * e[0][1];
	//开始先针对Y值 循环计算N次
	for (int i = 0; i < cycle; ++i)
	{
		y_value_plus.x1 = y_value[i].x1 + sigma * e[i][0];
		y_value_plus.x2 = y_value[i].x2 + sigma * e[i][1];
		y_value_minus.x1 = y_value[i].x1 - sigma * e[i][0];
		y_value_minus.x2 = y_value[i].x2 - sigma * e[i][1];

		if (MODEL_SEARCH_function_value(y_value_plus) < MODEL_SEARCH_function_value(y_value[i]))
		{
			y_value[i] = y_value_plus;
			cout<<"Plus value is selected ! +++"<<endl;
		}
		else if(MODEL_SEARCH_function_value(y_value_minus) < MODEL_SEARCH_function_value(y_value[i]))
		{
			y_value[i] = y_value_minus;
			cout<<"Minus value is selected ! ---"<<endl;
		}
		else
		{
			//y_value[i] = y_value;
			cout<<"Equal value is selected ! ==="<<endl;
		}
	}

	function_out(__FUNCTION__);

	return 0.0;
}


double MODEL_SEARCH_function_value(xx_vect var)
{
	function_in(__FUNCTION__);

	double result = 0.0;
	result = pow(var.x1, 2) + pow(var.x2, 2);

	function_out(__FUNCTION__);
	return result;
}
