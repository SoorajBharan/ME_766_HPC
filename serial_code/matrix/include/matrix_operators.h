#ifndef MATRIX_OPERATORS_H
#define MATRIX_OPERATORS_H

#include <iostream>
#include <random>
#include <type_traits>

namespace MatOperators {
template<typename Number>
class MatrixOperators
{
public:
	void fill_matrix_random(std::vector<std::vector<Number>> & mat,
				std::mt19937 mt1,
			 	Number minimum,
			  	Number maximum);

	void mat_x_mat(std::vector<std::vector<Number>> & mat_1,
			std::vector<std::vector<Number>> & mat_2,
			std::vector<std::vector<Number>> & mat_3);

	void print_matrix(std::vector<std::vector<Number>> & mat);
};

template<typename Number>
void
MatrixOperators<Number>::fill_matrix_random(std::vector<std::vector<Number>> & mat,
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

		
}

template<typename Number>
void
MatrixOperators<Number>::mat_x_mat(std::vector<std::vector<Number>> & mat_1,
				   std::vector<std::vector<Number>> & mat_2,
				   std::vector<std::vector<Number>> & mat_3)
{
	for(uint i=0; i<mat_1.size(); ++i){
		for (uint j=0; j<mat_2[i].size(); ++j) {
		mat_3[i][j]=static_cast<Number>(0.0);
			for(uint k=0; k<mat_1.size(); ++k){
				mat_3[i][j]+=mat_1[i][k]*mat_2[k][j];
			}
		}
	}
}

template<typename Number>
void
MatrixOperators<Number>::print_matrix(std::vector<std::vector<Number>> & mat)
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
