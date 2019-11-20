CC 	= g++ -std=c++0x -lpthread
CFLAGS 	= -Wall -O3
LDFLAGS = 

#----------

EXE = fluffypinkunicornsaregreat

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

#----------

$(EXE): $(OBJS)
	$(CC) $(OBJS) $(LIB_DIRS) $(LLIBS)$(LDFLAGS) -o $(EXE)

$(OBJS): %.o : %.cpp
	$(CC) $(CFLAGS) -c $<

#----------

clean:
	rm -f *.o *.*~ *~  $(EXE) 
