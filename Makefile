EXE = test

CXX = g++
CXXFLAGS = -I include -std=c++14

all: $(EXE)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): project.o 
	$(CXX) $^ -o $(EXE)

project.o: include/bst.hpp include/node.hpp include/iterator.hpp

format: $(SRC) include/bst.hpp include/node.hpp include/iterator.hpp
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	rm -rf *.o $(EXE) */*~ *~ a.out*

.PHONY: clean all format