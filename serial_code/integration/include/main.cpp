#include <iostream>
#include "enum_types.h"
#include "trapezoidal_integration.h"
#include "monte_carlo_method.h"
#include "random_number_generator.h"

double pi = 3.1415926535898;

int main(int argc, char ** argv)
{
	// Check if the user provided the input file directory
	/*if (argc != 2) {*/
	/*	std::cerr << "Usage: " << argv[0] << " <input_file_directory>" << std::endl;*/
	/*	return 1;*/
	/*}*/

	// Construct the full path to the input file
	/*std::string input_dir = argv[1];*/
	/*std::string input_file = input_dir;*/


	double x_min = -pi/2.0;
	double x_max = pi/2.0;
	int steps = 1e2;

	TrapezoidalInt::TrapezoidalIntegration<double> integrator_t(x_min, x_max, steps);
	integrator_t.run();

	MonteCarloInt::MonteCarloIntegration<double> integrator_m(x_min, x_max, steps);
	integrator_m.run();

	return 0;
}
