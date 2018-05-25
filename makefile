objects = main.o matrix.so
pattern = -Wall -g --std=c++11
matrix = BaseMatrix.cpp Matrix.cpp ColVector.cpp RowVector.cpp

run : main
	reset && ./main

main : $(objects)
	g++ $(objects) -o main -Wall -Wl,-rpath,./

main.o : main.cpp matrix.h
	g++ -c main.cpp -DMAIN $(pattern)

matrix.so : matrix.h $(matrix)
	g++ $(matrix) -o matrix.so -shared -fPIC $(pattern)


clean :
	rm main $(objects) -rf