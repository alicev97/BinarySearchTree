TEST1 = test_bst1  
TEST2 = test_bst2
TEST3 = test_node
CXX = g++
CXXFLAGS = -I include -std=c++14 -Wall -Wextra

all: $(TEST1) $(TEST2) $(TEST3)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(TEST1): test_bst1.o 
	$(CXX) $^ -o $(TEST1)

$(TEST2): test_bst2.o 
	$(CXX) $^ -o $(TEST2)

$(TEST3): test_node.o 
	$(CXX) $^ -o $(TEST3)

test_bst1.o: include/bst.hpp include/node.hpp include/iterator.hpp include/bits_bst.hpp
test_bst2.o: include/bst.hpp include/node.hpp include/iterator.hpp include/bits_bst.hpp
test_node.o: include/bst.hpp include/node.hpp include/iterator.hpp include/bits_bst.hpp


format: $(SRC) include/bst.hpp include/node.hpp include/iterator.hpp include/bits_bst.hpp
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	rm -rf *.o $(EXE) */*~ *~ a.out*

.PHONY: clean all format