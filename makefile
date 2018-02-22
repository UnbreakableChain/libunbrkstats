CXX = gcc -std=c11 
CXXFLAGS = -Wall -Wextra
TESTFLAGS = `pkg-config --cflags --libs glib-2.0`
INC=./include
LIBS=./libs
SRC=./src
OBJ=./obj
BIN=./bin
TEST=./tests
TESTBIN=$(BIN)/tests
DOXIFILE=./doc/doxys/Doxyfile.in


# Build release
release: CXXFLAGS += -O3
release: $(BIN)/libunbrkstats.a

# Build debug
debug: CXXFLAGS += -g
debug: $(BIN)/libunbrkstats.a

# Build library 
$(BIN)/libunbrkstats.a: $(OBJ)/ub_stats.o
	mkdir -p $(BIN)
	ar rc $@ $^ 

$(OBJ)/ub_stats.o: $(SRC)/ub_stats.c $(LIBS) $(INC)/ub_stats.h
	mkdir -p $(OBJ)
	$(CXX) -I$(LIBS)/libunbrkcore/include -I$(INC) $(CXXFLAGS) -c -o $@ $<


# Clean
clean:
	rm $(BIN)/* $(INC)/~* $(OBJ)/*.o


# Build documentation
doc: $(INC)/* $(DOXIFILE)
	doxygen $(DOXIFILE)


# Build and run tests
tests: $(TESTBIN)/ub_stats_tests

$(TESTBIN)/ub_stats_tests: $(TEST)/ub_stats_tests.c debug libraries 
	mkdir -p $(TESTBIN)
	$(CXX) -g -I$(INC) -I$(LIBS)/libunbrkcore/include $(CXXFLAGS) -o $@ $< -L$(BIN) -lunbrkstats -L$(LIBS)/libunbrkcore/bin -lunbrkcore $(TESTFLAGS)
	$@ 

libraries:
	make -C $(LIBS)/libunbrkcore
