EXE = test_bst1 

CXX = g++
CXXFLAGS = -I include -std=c++14 -Wall -Wextra

all: $(EXE)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): test_bst1.o 
	$(CXX) $^ -o $(EXE)

test_bst1.o: include/bst.hpp include/node.hpp include/iterator.hpp include/bits_bst.hpp

format: $(SRC) include/bst.hpp include/node.hpp include/iterator.hpp include/bits_bst.hpp
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	rm -rf *.o $(EXE) */*~ *~ a.out*

.PHONY: clean all format