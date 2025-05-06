CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = gene_bank
OBJECTS = customErrorClass.o geneBank.o mainSamples.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

customErrorClass.o: customErrorClass.cpp customErrorClass.h
	$(CXX) $(CXXFLAGS) -c customErrorClass.cpp

geneBank.o: geneBank.cpp geneBank.h
	$(CXX) $(CXXFLAGS) -c geneBank.cpp

mainSamples.o: mainSamples.cpp
	$(CXX) $(CXXFLAGS) -c mainSamples.cpp

clean:
	rm -f $(TARGET) *.o *.bin
