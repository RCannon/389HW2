CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -g

all: cache

cache: cache.o
	$(CXX) $(CXXFLAGS) -o cache cache.o

cache.o: cache.cc cache.hh
	$(CXX) $(CXXFLAGS) -c cache.cc
	
clean:
	rm -rf *.o cache
