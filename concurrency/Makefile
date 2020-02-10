CC 	= g++ -std=c++17 -pthread
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
