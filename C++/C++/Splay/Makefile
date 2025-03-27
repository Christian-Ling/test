INCLUDE_DIRS := folder
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := customErrorClass.o customErrorHandling.o
DEPS 		 := customErrorClass.h splay.h

.PHONY: clean all

all: customErrorClass.o splay.o splayOutput

clean:
	rm $(OBJS) splayOutput

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<


splay.o: splay.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mainsplay.o: mainsplay.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

splayOutput: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)