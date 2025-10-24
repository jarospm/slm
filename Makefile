CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = kgram
OBJS = main.o kgram.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: main.cpp kgram.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

kgram.o: kgram.cpp kgram.hpp
	$(CXX) $(CXXFLAGS) -c kgram.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean

