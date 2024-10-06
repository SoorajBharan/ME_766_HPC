#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <omp.h>

#include "matrix_operators.h"

int main(int argc, char **argv)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	if(argc != 3) {
		std::cerr << "Usage : " << argv[0] << "<number_of_threads" << " <size_of_matrix> " << std::endl;
		return 1;
	}
	int num_threads = atoi(argv[1]);
	uint mat_size = atoi(argv[2]);

	omp_set_num_threads(num_threads);

	double minimum = 0.0;
	double maximum = 100.0;

	MatOperators::MatrixOperators<double> mat_operators;
	std::vector<double> A(mat_size * mat_size);
	std::vector<double> B(mat_size * mat_size);
	std::vector<double> C(mat_size * mat_size);

	std::mt19937 mt1(time(0));
	std::mt19937 mt2(time(0)+1);
	mat_operators.fill_matrix_random(A, mt1, minimum, maximum, mat_size, mat_size);
	mat_operators.fill_matrix_random(B, mt2, minimum, maximum, mat_size, mat_size);
	mat_operators.mat_mult(A, B, C, mat_size, mat_size, mat_size);

	auto end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapse_time = end_time - start_time;
	std::cout << "Wall time = " << elapse_time.count();
	return 0;
}
