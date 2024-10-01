#include <iostream>
#include <vector>
#include <random>

#include "matrix_operators.h"

int main(int argc, char **argv)
{
	if(argc != 2) {
		std::cerr << "Usage : " << argv[0] << " <size_of_matrix> " << std::endl;
		return 1;
	}
	uint mat_size = atoi(argv[1]);

	std::vector<std::vector<int>> A(mat_size, std::vector<int>(mat_size));
	std::vector<std::vector<int>> B(mat_size, std::vector<int>(mat_size));
	std::vector<std::vector<int>> C(mat_size, std::vector<int>(mat_size));
	MatOperators::MatrixOperators<int> mat_operators;

	std::mt19937 mt1(time(0));
	std::mt19937 mt2(time(0)+1);

	mat_operators.fill_matrix_random(A, mt1, 0.0, 100);
	mat_operators.fill_matrix_random(B, mt2, 0.0, 100);
	mat_operators.mat_x_mat(A, B, C);
	std::cout << "Matrix A : " << std::endl;
	mat_operators.print_matrix(A);
	std::cout << "Matrix B : " << std::endl;
	mat_operators.print_matrix(B);
	std::cout << "Matrix C : " << std::endl;
	mat_operators.print_matrix(C);
	return 0;
}
