#ifndef MATRIX_OPERATORS_H
#define MATRIX_OPERATORS_H

#include <iostream>
#include <mpi.h>
#include <ostream>
#include <random>
#include <type_traits>
#include <chrono>

namespace MatOperators {
template<typename Number>
class MatrixOperators
{
public:
	typedef std::vector<std::vector<Number>> vectorised_matrix;
	void fill_vectorised_matrix_random(std::vector<Number> & vector_in,
				std::mt19937 mt,
				Number minimum,
				Number maximum,
				int rows,
				int cols);

	void mat_mult(std::vector<Number> & mat_1,
			std::vector<Number> & mat_2,
			std::vector<Number> & mat_3,
			int rows_1,
			int cols_2,
			int rows_2);

	void mat_mult_transpose(std::vector<Number> & mat_1,
			std::vector<Number> & mat_2,
			std::vector<Number> & mat_3,
			int rows_1,
			int cols_2,
			int rows_2);
	void print_vector_matrix(std::vector<Number> & mat,
				int rows,
				int cols);

	std::vector<Number> transpose(std::vector<Number> &,
					int rows,
					int cols);
};

template<typename Number>
void
MatrixOperators<Number>::fill_vectorised_matrix_random(std::vector<Number> & vector_in,
					    std::mt19937 mt,
					    Number minimum,
					    Number maximum,
					    int rows,
					    int cols)
{
	if constexpr (std::is_floating_point<Number>::value){
		std::uniform_real_distribution<Number> uni_distribution(minimum, maximum);
		for(uint i=0; i < rows; ++i) {
			for(uint j=0; j<cols; ++j){
				vector_in[i*cols + j] = uni_distribution(mt);
			}
		}
	}
	else if constexpr (std::is_integral<Number>::value) {
		std::uniform_int_distribution<Number> uni_distribution(minimum, maximum);
		for(uint i=0; i < rows; ++i) {
			for(uint j=0; j<cols; ++j){
				vector_in[i*cols + j] = uni_distribution(mt);
			}
		}
	}
	else {
		std::cerr << "Invalid datatype provided" << std::endl;
		exit(0);
	}

	std::cout << "Vector initialised with random values" << std::endl;
		
}
template<typename Number>
std::vector<Number>
MatrixOperators<Number>::transpose(std::vector<Number> & mat,
				   int rows,
				   int cols)
{
	std::vector<Number> mat_t(rows * cols);
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
MatrixOperators<Number>::mat_mult(std::vector<Number> & mat_1,
				  std::vector<Number> & mat_2,
				  std::vector<Number> & mat_3,
				  int rows_1,
				  int cols_2,
				  int rows_2)
{
	for (int i=0; i<rows_1; ++i) {
		for(int j=0; j<cols_2; ++j){
			mat_3[i*cols_2 + j] = 0;
			for(int k=0; k<rows_2; ++k){
				mat_3[i*cols_2 + j] += mat_1[i*rows_2 + k] * mat_2[j*cols_2 + k];
			}
		}	
	}

}
template<typename Number>
void
MatrixOperators<Number>::mat_mult_transpose(std::vector<Number> & mat_1,
				  std::vector<Number> & mat_2,
				  std::vector<Number> & mat_3,
				  int rows_1,
				  int cols_2,
				  int rows_2)
{
	long int local_k_count=0;
	long int global_k=0;
	for (int i=0; i<rows_1; ++i) {
		for(int j=0; j<cols_2; ++j){
			mat_3[i*cols_2 + j] = 0.0;
			for(int k=0; k<rows_2; ++k){
				mat_3[i*cols_2 + j] += mat_1[i*rows_2 + k] * mat_2[j*rows_2 + k];
				local_k_count++;
			}
		}	
	}
	MPI_Reduce(&local_k_count, &global_k, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	std::cout << "Matrix multiplication completed" << std::endl;
	std::cout << "Final k count : " << global_k << std::endl;
}

template<typename Number>
void
MatrixOperators<Number>::print_vector_matrix(std::vector<Number> & mat,
					     int rows,
					     int cols)
{
	for(int i=0; i<rows; ++i){
		std::cout << std::endl;
		for(int j=0; j<cols; ++j){
			std::cout << '\t' << mat[i*cols + j];
		}
	}
}

} // namespace MatOperators

#endif //MATRIX_OPERATORS_H
