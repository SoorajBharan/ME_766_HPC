#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "mpi.h"

#include "matrix_operators.h"

int main(int argc, char **argv)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	if(argc != 2) {
		std::cerr << "Usage : " << argv[0] << " <size_of_matrix> " << std::endl;
		return 1;
	}
	uint mat_size = atoi(argv[1]);
	double minimum = 0.0;
	double maximum = 100.0;

	MatOperators::MatrixOperators<double> mat_operators;
	std::vector<std::vector<double>> A(mat_size, std::vector<double>(mat_size));
	std::vector<std::vector<double>> B(mat_size, std::vector<double>(mat_size));
	std::vector<std::vector<double>> C(mat_size, std::vector<double>(mat_size));

	std::mt19937 mt1(time(0));
	std::mt19937 mt2(time(0)+1);
	mat_operators.fill_matrix_random(A, mt1, minimum, maximum);
	mat_operators.fill_matrix_random(B, mt2, minimum, maximum);
	mat_operators.mat_x_mat(A, B, C);

	auto end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapse_time = end_time - start_time;
	std::cout << "Wall time = " << elapse_time.count();
	return 0;
}
