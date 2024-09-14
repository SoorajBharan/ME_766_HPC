#include <iostream>
#include "enum_types.h"
#include "trapezoidal_integration.h"
#include "monte_carlo_method.h"
#include "random_number_generator.h"

int main(int argc, char ** argv)
{
	// Check if the user provided the input file directory
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <input_file_directory>" << std::endl;
		return 1;
	}

	// Construct the full path to the input file
	std::string input_dir = argv[1];
	std::string input_file = input_dir + "/input.json";

	MonteCarloInt::MonteCarloIntegration<double> integrator;
	integrator.read_from_json(input_file);
	integrator.print_input();
	srand(static_cast<unsigned int>(time(0)));
	integrator.solve();
	integrator.print_results();

	return 0;
}
