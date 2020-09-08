#!/bin/bash

./hw_properties > hw_properties.txt

./square_parallel

./vec_parallel

./square_serial

gprof square_serial gmon.out > square_serial_analysis.txt

rm gmon.out

./vector_add_serial

gprof vector_add_serial gmon.out > vector_serial_analysis.txt

rm gmon.out
