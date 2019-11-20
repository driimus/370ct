CC 	= g++
CFLAGS 	= -Wall -O3 -fopenmp -std=c++0x 
LDFLAGS = -lgomp

#----------

EXE = learnhowtoeditmakefiles

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

#----------

$(EXE): $(OBJS)
	$(CC) $(OBJS) $(LIB_DIRS) $(LLIBS)$(LDFLAGS) -o $(EXE)

$(OBJS): %.o : %.cpp
	$(CC) $(CFLAGS) -c $<

#----------

clean:
	rm -f *.o *.*~ *~  $(EXE) 
