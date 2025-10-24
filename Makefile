CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = slm
SRCDIR = src
OBJS = main.o training.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: $(SRCDIR)/main.cpp $(SRCDIR)/training.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp

training.o: $(SRCDIR)/training.cpp $(SRCDIR)/training.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/training.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean

