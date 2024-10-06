#ifndef MATRIX_OPERATORS_H
#define MATRIX_OPERATORS_H

#include <algorithm>
#include <iostream>
#include <ostream>
#include <random>
#include <type_traits>
#include <chrono>
#include "omp.h"

namespace MatOperators {
template<typename Number>
class MatrixOperators
{
public:
	typedef std::vector<Number> vectorised_matrix;
	void fill_matrix_random(vectorised_matrix & mat,
				std::mt19937 mt1,
			 	Number minimum,
			  	Number maximum,
				int rows,
				int cols);

	void mat_mult(vectorised_matrix & mat_1,
			vectorised_matrix & mat_2,
			vectorised_matrix & mat_3,
			int rows_1,
			int cols_2,
			int rows_2);

	void print_matrix(vectorised_matrix & mat,
			int rows,
			int cols);

	std::vector<Number> transpose(vectorised_matrix &,
					int rows,
					int cols);
};

template<typename Number>
void
MatrixOperators<Number>::fill_matrix_random(vectorised_matrix & mat,
					    std::mt19937 mt1,
					    Number minimum,
					    Number maximum,
					    int rows,
					    int cols)
{
	if constexpr (std::is_floating_point<Number>::value){
		std::uniform_real_distribution<Number> uni_distribution(minimum, maximum);
		for(uint i=0; i < rows; ++i) {
			for(uint j=0; j<cols; ++j){
				mat[i*cols+j] = uni_distribution(mt1);
			}
		}
	}
	else if constexpr (std::is_integral<Number>::value) {
		std::uniform_int_distribution<Number> uni_distribution(minimum, maximum);
		for(uint i=0; i < rows; ++i) {
			for(uint j=0; j<cols; ++j){
				mat[i*cols+j] = uni_distribution(mt1);
			}
		}
	}
	else {
		std::cerr << "Invalid datatype provided" << std::endl;
		exit(0);
	}

	std::cout << "Matrix initialised with random values" << std::endl;
		
}

template<typename Number>
std::vector<Number>
MatrixOperators<Number>::transpose(vectorised_matrix & mat,
				   int rows,
				   int cols)
{
	vectorised_matrix mat_t(cols * rows);
	for(uint i=0; i<rows; ++i){
		for(uint j=0; j<cols; ++j){
			mat_t[j*rows+i]=mat[i*cols+j];
		}
	}
	std::cout << "Matrix transpose calculated" << std::endl;
	return mat_t;
}

template<typename Number>
void
MatrixOperators<Number>::mat_mult(vectorised_matrix & mat_1,
				   vectorised_matrix & mat_2,
				   vectorised_matrix & mat_3,
				  int rows_1,
				  int cols_2,
				  int rows_2)
{
	double problem_size = rows_1 * cols_2 * rows_2;
	double percent_completed = 0.0;
	// Initialize C
	std::fill(mat_3.begin(), mat_3.end(), 0.0);
	std::cout << "Resultant matrix initialised with zeros" << std::endl;
	vectorised_matrix mat_2_T = transpose(mat_2, rows_2, cols_2);
	uint i,j,k;
	std::cout << "Matrix Multiplication initialised " << std::endl;

	#pragma omp parallel for private(i, j, k) shared(mat_1, mat_2_T, mat_3) reduction(+:percent_completed)
	for(i=0; i<rows_1; ++i){
		for (j=0; j<cols_2; ++j) {
			for(k=0; k<rows_2; ++k){
				mat_3[i*cols_2 + j] += mat_1[i*rows_2 + k] * mat_2_T[j*cols_2 + k];
				percent_completed++;
			}
		}
	}
	std::cout << " \n Final count for k : " << percent_completed << std::endl;
	std::cout << " problem size : " << problem_size << std::endl;
	std::cout << "Final counts \n i = " << i << "; j = " << j << "; k = " << k << std::endl;
}

template<typename Number>
void
MatrixOperators<Number>::print_matrix(vectorised_matrix & mat,
				      int rows,
				      int cols)
{
	for(uint i=0; i<rows; ++i){
		std::cout << std::endl;
		for(uint j=0; j<cols; ++j) {
			std::cout << '\t' << mat[i*cols+j];
		}
	}
	std::cout << std::endl;
}

} // namespace MatOperators

#endif //MATRIX_OPERATORS_H
