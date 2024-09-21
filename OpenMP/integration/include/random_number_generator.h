#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include "enum_types.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <time.h>

namespace RandomNum
{
template<typename Number>
class RandomNumberGenerator
{
private:
	Number random_number;
	Number minimum, maximum;
public:
	RandomNumberGenerator(Number min,Number max)
	: generator_type(RandomValueGeneratorType::RandomFunction)
	{
		minimum = min;
		maximum = max;
	}

	RandomValueGeneratorType generator_type;
	void set_range(Number,Number);
	Number get_random_value();
	void compute_by_function();
	void compute_by_normal_distribution();
};

template<typename Number>
void RandomNumberGenerator<Number>::set_range(Number min, Number max)
{
	minimum = min;
	maximum = max;
}

template<typename Number>
Number RandomNumberGenerator<Number>::get_random_value()
{
	if(generator_type==RandomValueGeneratorType::NormalDistribution)
	{
		compute_by_normal_distribution();
	}
	else if(generator_type==RandomValueGeneratorType::RandomFunction)
	{
		compute_by_function();
	}
	else
	{
		std::cerr << "Error : Unknown generator type - " << std::endl;
		exit(0);
	}

	return random_number;
}

template<typename Number>
void RandomNumberGenerator<Number>::compute_by_function()
{
	/*Number temp = static_cast<Number>(rand() / static_cast<Number>(RAND_MAX));*/
	/*random_number = minimum + (temp* (maximum - minimum));*/
	// Ensure the seed is initialized
	int rand_int = rand() % 1001;
	random_number = minimum + ((maximum - minimum)* rand_int / 1000.0);
}

template<typename Number>
void RandomNumberGenerator<Number>::compute_by_normal_distribution()
{
	std::random_device rd;  // Seed generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<> dis(minimum, maximum); // Range [0.0, 1.0)

	random_number = dis(gen);
}

} // end of RandomNum

#endif // RANDOM_NUMBER_GENERATOR_H
