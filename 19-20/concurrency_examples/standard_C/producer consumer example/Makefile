#################################################
# Makefile for 370ct                            #
#################################################

CC = gcc
CFLAGS = -Wall 
LLIBS =  -lm -lpthread
EXE = prodcon 

OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

#----------
hmx: $(OBJS)
	$(CC) $(LLIBS) $(OBJS)  -o $(EXE)
	rm -f *.o *~

#----------

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $<

#----------

clean:
	rm -f *.o *.*~ *~  $(EXE)

#----------


