#ifndef TRAPEZOIDAL_INTEGRATION_H
#define TRAPEZOIDAL_INTEGRATION_H

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace TrapezoidalInt
{
template<typename Number>
Number value_function(Number value)
{
	return (value * value);
}

template<class Number>
class TrapezoidalIntegration {
private:
	Number upper_limit;
	Number lower_limit;
	Number sum;
	int intervals;
	Number step_size;

public:
	TrapezoidalIntegration()
	: lower_limit(0),
	upper_limit(1),
	intervals(100)
{
		step_size = (upper_limit - lower_limit) / intervals;
	}

	void read_from_json(const std::string& filename);
	void solve();
	void print_input() const;
	void print_results() const;
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

/*
 * Prints the input parameters on the screen
 * */
template<class Number>
void TrapezoidalIntegration<Number>::print_input() const
{
	std::cout << " \t\t INPUT PARAMETERS " << std::endl;
	std::cout << "Upper Limit : " << upper_limit << std::endl;
	std::cout << "Lower limit : " << lower_limit << std::endl;
	std::cout << "Intervals : " << intervals << std::endl;
	std::cout << "Step size : " << step_size << std::endl;
}

template<class Number>
void TrapezoidalIntegration<Number>::print_results() const
{
	std::cout << "\t\t OUTPUT PARAMETERS" << std::endl;
	std::cout << "Integral value : " << sum << std::endl;
}
} // end of naemspace TrapezoidalInt
#endif // TRAPEZOIDAL_INTEGRATION_H
