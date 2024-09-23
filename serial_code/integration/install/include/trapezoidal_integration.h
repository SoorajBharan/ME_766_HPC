#ifndef TRAPEZOIDAL_INTEGRATION_H
#define TRAPEZOIDAL_INTEGRATION_H

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <cmath>

using json = nlohmann::json;

namespace TrapezoidalInt
{

double pi = 3.1415926535898;

template<typename Number>
Number value_function(Number value)
{
	return cos(value);
}

template<class Number>
class TrapezoidalIntegration {
private:
	Number upper_limit;
	Number lower_limit;
	Number sum;
	long int intervals;
	Number step_size;

public:
	TrapezoidalIntegration(double x_min, double x_max, int steps)
	: lower_limit(0),
	upper_limit(1),
	intervals(100)
{
		lower_limit = x_min;
		upper_limit = x_max;
		intervals = steps;
		step_size = (upper_limit - lower_limit) / intervals;
	}

	void read_from_json(const std::string& filename);
	void set_parameters();
	void solve();
	void print_input() const;
	void print_results() const;
	void run();
};
/*
 * This function reads in values for class member varible from input.json file
 * */
template<class Number>
void TrapezoidalIntegration<Number>::read_from_json(const std::string& filename)
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
}

/*
 * Following function is used to hard code the input parameters in the problem
 */
template<class Number>
void TrapezoidalIntegration<Number>::set_parameters()
{
	lower_limit = -1 * pi / 2.0;
	upper_limit = pi / 2.0;
	intervals = 1e9;
	step_size = (upper_limit - lower_limit)/ intervals;
}

/*
 *	sum = \frac{h}{2} \left( f(x_0) + f(x_n) + 2*\sum_{i=1}^{n-1} f(x_i) \right)
 */
template<class Number>
void TrapezoidalIntegration<Number>::solve()
{
	sum = ( value_function(upper_limit) + value_function(lower_limit));
	for(uint i = 1; i < intervals-1; ++i)
		sum+=2 * value_function(lower_limit + (i * step_size));
	sum *= step_size / 2.0;
}

template<class Number>
void TrapezoidalIntegration<Number>::run()
{
	/*set_parameters();*/
	print_input();
	solve();
	print_results();
}

/*
 * Prints the input parameters on the screen
 * */
template<class Number>
void TrapezoidalIntegration<Number>::print_input() const
{
	std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
	std::cout << "% \t\t TRAPEZOIDAL INTEGRATION METHOD \t\t%" << std::endl;
	std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
	std::cout << "\t\t\t INPUT PARAMETERS" << std::endl;
	std::cout << "Upper Limit : " << upper_limit << std::endl;
	std::cout << "Lower limit : " << lower_limit << std::endl;
	std::cout << "Intervals : " << intervals << std::endl;
	std::cout << "Step size : " << step_size << std::endl;
}

template<class Number>
void TrapezoidalIntegration<Number>::print_results() const
{
	std::cout << "\t\t\t OUTPUT PARAMETERS" << std::endl;
	std::cout << "Integral value : " << sum << std::endl;
	std::cout << "Error : " << std::abs(sum-2.0) << std::endl; 
}
} // end of naemspace TrapezoidalInt
#endif // TRAPEZOIDAL_INTEGRATION_H
