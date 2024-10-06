#ifndef MATRIX_OPERATORS_H
#define MATRIX_OPERATORS_H

#include <iostream>
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
	void fill_matrix_random(vectorised_matrix & mat,
				std::mt19937 mt1,
			 	Number minimum,
			  	Number maximum);

	void mat_x_mat(vectorised_matrix & mat_1,
			vectorised_matrix & mat_2,
			vectorised_matrix & mat_3);

	void print_matrix(vectorised_matrix & mat);

	std::vector<std::vector<Number>> transpose(vectorised_matrix &);
};

template<typename Number>
void
MatrixOperators<Number>::fill_matrix_random(vectorised_matrix & mat,
					    std::mt19937 mt1,
					    Number minimum,
					    Number maximum)
{
	if constexpr (std::is_floating_point<Number>::value){
		std::uniform_real_distribution<Number> uni_distribution(minimum, maximum);
		for(uint i=0; i < mat.size(); ++i) {
			for(uint j=0; j<mat[i].size(); ++j){
				mat[i][j] = uni_distribution(mt1);
			}
		}
	}
	else if constexpr (std::is_integral<Number>::value) {
		std::uniform_int_distribution<Number> uni_distribution(minimum, maximum);
		for(uint i=0; i < mat.size(); ++i) {
			for(uint j=0; j<mat[i].size(); ++j){
				mat[i][j] = uni_distribution(mt1);
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
std::vector<std::vector<Number>>
MatrixOperators<Number>::transpose(vectorised_matrix & mat)
{
	uint rows = mat.size();
	uint cols = mat[0].size();
	vectorised_matrix mat_t(cols, std::vector<Number>(rows));
	for(uint i=0; i<rows; ++i){
		for(uint j=0; j<cols; ++j){
			mat_t[i][j]=mat[j][i];
		}
	}
	std::cout << "Matrix transpose calculated" << std::endl;
	return mat_t;
}

template<typename Number>
void
MatrixOperators<Number>::mat_x_mat(vectorised_matrix & mat_1,
				   vectorised_matrix & mat_2,
				   vectorised_matrix & mat_3)
{
	uint mat_1_row = mat_1.size();
	uint mat_2_col = mat_2[0].size();
	uint mat_1_col = mat_1[0].size();
	double problem_size = mat_1_row * mat_1_col * mat_2_col;
	double percent_completed = 0.0;
	// Initialize C
	for (uint i = 0; i < mat_1_row; ++i) {
		std::fill(mat_3[i].begin(), mat_3[i].end(), static_cast<Number>(0));
	}
		std::cout << "Resultant matrix initialised with zeros" << std::endl;
	vectorised_matrix mat_2_T = transpose(mat_2);
	uint i,j,k;
	std::cout << "Matrix Multiplication initialised " << std::endl;
	for(i=0; i<mat_1_row; ++i){
		for (j=0; j<mat_2_col; ++j) {
			for(k=0; k<mat_1_col; ++k){
				mat_3[i][j]+=mat_1[i][k]*mat_2[j][k];
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
MatrixOperators<Number>::print_matrix(vectorised_matrix & mat)
{
	for(uint i=0; i<mat.size(); ++i){
		std::cout << std::endl;
		for(uint j=0; j<mat[i].size(); ++j) {
			std::cout << '\t' << mat[i][j];
		}
	}
	std::cout << std::endl;
}

} // namespace MatOperators

#endif //MATRIX_OPERATORS_H
