#ifndef MONTE_CARLO_INTEGRATION_H
#define MONTE_CARLO_INTEGRATION_H

#include <fstream>
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <nlohmann/json.hpp>
#include "enum_types.h"
#include "random_number_generator.h"

using json = nlohmann::json;

namespace MonteCarloInt
{
double pi = 3.1415926535898;
template<typename Number>
Number value_function(Number value)
{
	return cos(value);
}

template<class Number>
class MonteCarloIntegration {
private:
	Number upper_limit;
	Number lower_limit;
	Number sum;
	int intervals;
	Number step_size;
	Number minimum_value, maximum_value;
	int in_points,tot_points;

public:
	MonteCarloIntegration(double x_min, double x_max, int steps)
	: lower_limit(0),
	upper_limit(1),
	intervals(100),
	generator_type(RandomValueGeneratorType::RandomFunction)
	{
		lower_limit = x_min;
		upper_limit = x_max;
		intervals = steps;
		step_size = (upper_limit - lower_limit) / intervals;
	}

	RandomValueGeneratorType generator_type;
	void read_from_json(const std::string& filename);
	void set_parameters();
	void max_min();
	void solve();
	void print_input() const;
	void print_results() const;
	void run();
};

template<class Number>
void MonteCarloIntegration<Number>::max_min()
{
	minimum_value = value_function(lower_limit);
	maximum_value = minimum_value;
	Number temp;
	for(uint i = 0; i < intervals; ++i)
	{
		temp = value_function(lower_limit+(i*step_size));
		if(temp < minimum_value)
			minimum_value = temp;
		else if (temp > maximum_value)
			maximum_value = temp;
      ;
	}

}

template<class Number>
void MonteCarloIntegration<Number>::read_from_json(const std::string& filename)
{
	std::ifstream file(filename);
	if(!file.is_open())
	{
		std::cerr << " Error: could not open file " << filename << std::endl;
		exit(0);
	}

	json json_file;
	//output file to json_file
	file >> json_file;

	lower_limit = json_file.value("lower_limit", lower_limit);
	upper_limit = json_file.value("upper_limit", upper_limit);
	intervals = json_file.value("intervals", intervals);

	step_size = (upper_limit - lower_limit) / intervals;

	max_min();
}

/*
 * Following function is used to hard code the input parameters in the problem
 */
template<class Number>
void MonteCarloIntegration<Number>::set_parameters()
{
	lower_limit = -1 * pi / 2.0;
	upper_limit = pi / 2.0;
	intervals = 1e5;
	step_size = (upper_limit - lower_limit)/ intervals;
}

/*
 *	sum = \frac{h}{2} \left( f(x_0) + f(x_n) + 2*\sum_{i=1}^{n-1} f(x_i) \right)
 */
template<class Number>
void MonteCarloIntegration<Number>::solve()
{
	Number random_xvalue,random_yvalue,temp;
	RandomNum::RandomNumberGenerator<Number> random_gen_x(lower_limit, upper_limit);
	RandomNum::RandomNumberGenerator<Number> random_gen_y(minimum_value, maximum_value);
	Number tot_sum = (maximum_value - minimum_value) * (upper_limit - lower_limit);
	tot_points = 0;
	in_points = 0;
	srand(static_cast<unsigned int>(time(0)));
	for(uint i = 0; i < intervals; ++i)
	{
		random_xvalue = random_gen_x.get_random_value();
		random_yvalue = random_gen_y.get_random_value();

     /*std::cout << "Random x : " << random_xvalue << std::endl;*/
     /*std::cout << "Random y : " << random_yvalue << std::endl;*/

		temp = value_function(random_xvalue);
		if(temp >= 0)
		{
			if((random_yvalue <= temp) && (random_yvalue >= 0))
			{in_points++;}
		}
		else
	{
			if((random_yvalue >= temp) && (random_yvalue < 0))
			{in_points--;}
		}

		tot_points++;

	}
	sum = tot_sum * in_points / tot_points;	
}

template<class Number>
void MonteCarloIntegration<Number>::run()
{
	/*set_parameters();*/
	max_min();
	print_input();
	srand(static_cast<unsigned int>(time(0)));
	solve();
	print_results();
}

template<class Number>
void MonteCarloIntegration<Number>::print_input() const
{
	std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
	std::cout << "% \t\t MONTE-CARLO INTEGRATION METHOD \t\t%" << std::endl;
	std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
	std::cout << " \t\t\t INPUT PARAMETERS " << std::endl;
	std::cout << "Upper Limit : " << upper_limit << std::endl;
	std::cout << "Lower limit : " << lower_limit << std::endl;
	std::cout << "Intervals : " << intervals << std::endl;
	/*std::cout << "Step size : " << step_size << std::endl;*/
	if(generator_type==RandomValueGeneratorType::RandomFunction)
	std::cout << "Random Value Generator method : RandomFunction" << std::endl;
	else if(generator_type==RandomValueGeneratorType::NormalDistribution)
	std::cout << "Random Value Generator method : NormalDistribution" << std::endl;
}

template<class Number>
void MonteCarloIntegration<Number>::print_results() const
{
	std::cout << "\t\t\t OUTPUT PARAMETERS" << std::endl;
	std::cout << "Minimum function value : " << minimum_value << std::endl;
	std::cout << "Maximum function value : " << maximum_value << std::endl;
	std::cout << "Number of points inside the curve and above xaxis : " << in_points << std::endl;
	std::cout << "Total number of points : " << tot_points << std::endl;
	std::cout << "Integral value : " << sum << std::endl;
	std::cout << "Error : " << std::abs(sum - 2.0) << std::endl;
}
} // end of namespace MonteCarloInt

#endif // MONTE_CARLO_INTEGRATION_H
