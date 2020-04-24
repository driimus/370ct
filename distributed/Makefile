CXX 	= mpic++
CXXFLAGS 	= -Wall -fopenmp -std=c++11
LDFLAGS = -lgomp -lz

#----------

EXES = part_one part_2-3 part_four

all: $(EXES)

#----------

%: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

#----------

clean:
	rm -f $(EXES)
