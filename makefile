CXX = g++ -std=c++11 -g
SRCS = matrix.cpp interface.cpp main.cpp
HEADERS = matrix.hpp interface.hpp
LinearAlgebra: ${SRCS} ${HEADERS}
	${CXX} ${SRCS} -o LinearAlgebra