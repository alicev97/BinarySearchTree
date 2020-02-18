EXE = test_bst1.x test_bst2.x test_node.x
OBJ = $(EXE:.x=.o)
CXX = g++
CXXFLAGS = -I include -std=c++14 -Wall -Wextra

all: $(EXE)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

%.x: %.o
	$(CXX) -o $@ $< 

test_bst1.o: include/bst.hpp include/node.hpp include/iterator.hpp include/bits_bst.hpp
test_bst2.o: include/bst.hpp include/node.hpp include/iterator.hpp include/bits_bst.hpp
test_node.o: include/node.hpp

clean:
	rm -rf *.o *.x

.PHONY: clean all