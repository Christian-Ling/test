INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := customErrorClass.o rb.o avlmain.o
DEPS 		 := ${INCLUDE_DIRS}/customErrorClass.h ${INCLUDE_DIRS}/rb.h

.PHONY: clean all

all: customErrorClass.o rb.o avlmain.o avlOutput

clean:
	rm $(OBJS) avlOutput

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

avl.o: avl.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

avlmain.o: avlmain.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

avlOutput: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)