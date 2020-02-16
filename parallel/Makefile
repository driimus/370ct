CXX = g++
CXXFLAGS = -std=c++11 -fopenmp -Wall -O3
LDFLAGS = -lgomp

#----------

EXE = app

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

#----------

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(EXE)

$(OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
#----------

clean:
	rm -f *.o *.*~ *~  $(EXE)
clean-o:
	rm -f *.o
