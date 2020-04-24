CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall -O3

#----------

EXE = part_1-3

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

#----------

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(EXE)

$(OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
#----------

clean:
	rm -f *.o *.*~ *~  $(EXE)
clean-o:
	rm -f *.o
