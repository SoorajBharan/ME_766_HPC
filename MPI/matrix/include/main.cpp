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
	MPI_Init(&argc, &argv);

	const int mat_size = atoi(argv[1]);
	double minimum = 0.0;
	double maximum = 100.0;
	const int root = 0;

	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int rows_per_core = mat_size / size;
	int remaining_rows = mat_size % size;
	int local_rows = (rank==size-1)?(rows_per_core+remaining_rows): (rows_per_core);

	std::vector<double> global_A;
	std::vector<double> global_B;
	std::vector<double> global_B_transpose;
	std::vector<double> global_C;
	std::vector<double> local_A;
	std::vector<double> local_C;
	if(rank==0){
		global_A.resize(mat_size*mat_size);
		global_B.resize(mat_size*mat_size);
		global_C.resize(mat_size*mat_size);
	}
	global_B_transpose.resize(mat_size*mat_size);
	local_A.resize(local_rows*mat_size);
	local_C.resize(local_rows*mat_size);

	MatOperators::MatrixOperators<double> mat_operators;
	std::mt19937 mt1(time(0)+rank);

	mat_operators.fill_vectorised_matrix_random(local_A, mt1, minimum, maximum, local_rows, mat_size);
	// Prepare to gather
	std::vector<int> recvcounts(size, local_rows);
	std::vector<int> displs(size);

	// Set recvcounts and displs
	for (int i = 0; i < size; ++i) {
		int rows = (i == size - 1) ? (rows_per_core + remaining_rows) : rows_per_core;
		recvcounts[i] = rows * mat_size; // Total elements to receive from each process
		displs[i] = (i == 0) ? 0 : displs[i - 1] + recvcounts[i - 1]; // Cumulative offset
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==0){
		std::mt19937 mt2(time(0)+size);
		mat_operators.fill_vectorised_matrix_random(global_B, mt2, minimum,  maximum, mat_size, mat_size);
		global_B_transpose=mat_operators.transpose(global_B, mat_size, mat_size);
	}
	MPI_Bcast(global_B_transpose.data(), mat_size*mat_size, MPI_DOUBLE, root, MPI_COMM_WORLD);
	mat_operators.mat_mult_transpose(local_A, global_B_transpose, local_C, local_rows, mat_size, mat_size);


	// Gather the local matrices into the global matrix at the root
	MPI_Gatherv(local_C.data(),
			local_C.size(),
			MPI_DOUBLE,
			global_C.data(),
			recvcounts.data(),
			displs.data(),
			MPI_DOUBLE,
			root,
			MPI_COMM_WORLD);

	// Gather the local matrices into the global matrix at the root
	MPI_Gatherv(local_A.data(),
			local_A.size(),
			MPI_DOUBLE,
			global_A.data(),
			recvcounts.data(),
			displs.data(),
			MPI_DOUBLE,
			root,
			MPI_COMM_WORLD);
	if(rank==0){
		std::cout << "\nMatrix A " << std::endl;
		mat_operators.print_vector_matrix(global_A, mat_size, mat_size);
		std::cout << "\nMatrix B " << std::endl;
		mat_operators.print_vector_matrix(global_B, mat_size, mat_size);
		std::cout << "\nMatrix B transpose " << std::endl;
		mat_operators.print_vector_matrix(global_B_transpose, mat_size, mat_size);
		std::cout << "\nMatrix C " << std::endl;
		mat_operators.print_vector_matrix(global_C, mat_size, mat_size);
		auto end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapse_time = end_time - start_time;
		std::cout << "\nWall time = " << elapse_time.count();
	}
	MPI_Finalize();
	return 0;
}
