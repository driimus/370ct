CXX = g++
CXXFLAGS = -std=c++11 -fopenmp -Wall -O3
LDFLAGS = -lgomp

#----------

EXES = part_1-2 part_3-4

all: $(EXES)

#----------

%: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

#----------

clean:
	rm -f $(EXES)
