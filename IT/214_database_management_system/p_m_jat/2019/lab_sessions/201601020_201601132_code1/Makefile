default: hw_properties square_parallel vec_parallel square_set_numbers vector_add

hw_properties: hw_properties.cu
	nvcc hw_properties.cu -o hw_properties

square_parallel: square_parallel.cu
	nvcc square_parallel.cu -o square_parallel

vec_parallel: vec_parallel.cu
	nvcc vec_parallel.cu -o vec_parallel

square_set_numbers: square_set_numbers.c
	gcc square_set_numbers.c -o square_serial -lm -pg

vector_add: vector_add.c
	gcc vector_add.c -o vector_add_serial -lm -pg

clean:
	rm hw_properties square_parallel vec_parallel square_serial vector_add_serial
