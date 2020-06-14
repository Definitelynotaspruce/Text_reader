CXX = g++
CXXFLAGS = -Wall -std=c++17 -pedantic -O3
LD_FLAGS = -lgtest -lpthread

NAME = main

#PATH_TO_SRC := src/
SRC_FILES = $(wildcard $(PATH_TO_SRC)*.cpp)

OBJECT_OUT = $(SRC_FILES:.cpp=.o)

default: $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $(NAME)  $^ 

.PHONY: build
build: $(SRC_FILES)
	mkdir -p build
	$(CXX) -c $^ $(CXXFLAGS)
	mv $(OBJECT_OUT) build

.PHONY: clean
clean:
	rm -f *.o $(NAME) 
	rm result.txt

.PHONY: cleanall
cleanall:
	rm -f *.o $(NAME)
	rm -R build