CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -g

all: test_cache_lib

test_cache_lib: test_cache_lib.o cache_lib.o
	$(CXX) $(CXXFLAGS) -o test_cache_lib test_cache_lib.o cache_lib.o

test_cache_lib.o: test_cache_lib.cc cache.hh
	$(CXX) $(CXXFLAGS) -c test_cache_lib.cc

cache_lib.o: cache_lib.cc cache.hh
	$(CXX) $(CXXFLAGS) -c cache_lib.cc
	
clean:
	rm -rf *.o test_cache_lib
