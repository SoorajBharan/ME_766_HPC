#include <iostream>
#include "enum_types.h"
#include "trapezoidal_integration.h"
#include "monte_carlo_method.h"
#include "random_number_generator.h"
#include <omp.h>

int main(int argc, char ** argv)
{
	omp_set_num_threads(4);
	// Check if the user provided the input file directory
	/*if (argc != 2) {*/
	/*	std::cerr << "Usage: " << argv[0] << " <input_file_directory>" << std::endl;*/
	/*	return 1;*/
	/*}*/

	// Construct the full path to the input file
	/*std::string input_dir = argv[1];*/
	/*std::string input_file = input_dir;*/

	/*TrapezoidalInt::TrapezoidalIntegration<double> integrator_t;*/
	/*integrator.read_from_json(input_file);*/
	/*integrator_t.set_parameters();*/
	/*integrator_t.print_input();*/
	/*srand(static_cast<unsigned int>(time(0)));*/
	/*integrator_t.solve();*/
	/*integrator_t.print_results();*/

	MonteCarloInt::MonteCarloIntegration<double> integrator_m;
	/*integrator.read_from_json(input_file);*/
	integrator_m.set_parameters();
	integrator_m.max_min();
	integrator_m.print_input();
	srand(static_cast<unsigned int>(time(0)));
	integrator_m.solve();
	integrator_m.print_results();

	return 0;
}
