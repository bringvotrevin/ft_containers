.PHONY: vector
vector:
	c++ vector_unittest.cpp -g -std=c++11 -I $(shell brew --prefix googletest)/include -L $(shell brew --prefix googletest)/lib -lgtest -o vector_unittest
	./vector_unittest
