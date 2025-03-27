INCLUDE_DIRS := /home/user/Documents/CSC310/MakeFiles/Version3/
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

#lots of reduntant information that could change

errorTutorial: customErrorClass.o customErrorHandling.o
	$(CC) -o errorTutorial customErrorClass.o customErrorHandling.o $(CFLAGS)

customErrorClass.o: customErrorClass.cpp customErrorClass.h
	$(CC) -c -o customErrorClass.o customErrorClass.cpp $(CFLAGS)

customErrorHandling.o: customErrorHandling.cpp customErrorClass.h
	$(CC) -c -o customErrorHandling.o customErrorHandling.cpp $(CFLAGS)