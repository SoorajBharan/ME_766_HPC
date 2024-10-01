gprof ./matrix_omp gmon.out > profile.txt
gprof2dot profile.txt -o profile.dot
dot -Tpng profile.dot -o profile.png
